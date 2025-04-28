#include "PcfBindingHandler.h"
#include "../../gen/model/PcfBinding.h"
#include "../Service/IPcfBindingService.h"
#include "userver/components/component_context.hpp"

PcfBindingHandler::PcfBindingHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
        m_service(context.FindComponent<std::shared_ptr<IPcfBindingService>>("pcf-binding-service"))
{}

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

        return  userver::formats::json::ToString(response.ExtractValue());
    } catch (const std::invalid_argument &e) { // validation error

    } catch (const std::exception &e) { // bad request 500

    }
}

