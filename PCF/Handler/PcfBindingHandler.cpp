#include "PcfBindingHandler.h"

#include <iostream>

#include "../../gen/model/PcfBinding.h"
#include "../Service/IPcfBindingService.h"
#include "userver/components/component_context.hpp"
#include "../Service/PcfBindingServiceComponent.h"

// PcfBindingHandler::PcfBindingHandler(
//     const userver::components::ComponentConfig& config,
//     const userver::components::ComponentContext& context)
//     : HttpHandlerBase(config, context),
//         m_service(context.FindComponent<std::shared_ptr<IPcfBindingService>>("pcf-binding-service"))
// {}

PcfBindingHandler::PcfBindingHandler(
const userver::components::ComponentConfig& config,
const userver::components::ComponentContext& context)
: HttpHandlerBase(config, context)
{
    auto& service_component = context.FindComponent<PcfBindingServiceComponent>();
    m_service = service_component.GetService();
}

std::string PcfBindingHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest &request,
    userver::server::request::RequestContext &context)
const {
    try {
        const auto& body = request.RequestBody();
        org::openapitools::server::model::PcfBinding binding;
        binding.fromJsonString(body);

        const auto uuid = m_service->Register(binding);

        userver::formats::json::ValueBuilder response;
        response["uuid"] = uuid;

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated); // created 200
        request.GetHttpResponse().SetHeader(
            std::string("Location"),
            "/nbsf-management/v1/pcfBindings/" + std::to_string(uuid));

        return  binding.toJsonString(true); // json request. Can add uuid via: userver::formats::json::ToString(response.ExtractValue())
    } catch (const std::invalid_argument &e) { // validation error 400
        userver::formats::json::ValueBuilder error;
        error["message"] = e.what();
        std::cerr << "Validation failed: " << e.what() << std::endl;
        throw userver::server::handlers::RequestParseError(error.ExtractValue());
    } catch (const std::exception &e) { // bad request 500
        userver::formats::json::ValueBuilder error;
        error["message"] = "Internal service error";
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}
