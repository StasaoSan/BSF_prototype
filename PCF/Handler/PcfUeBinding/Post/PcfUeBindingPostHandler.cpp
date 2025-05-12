#include "PcfUeBindingPostHandler.h"
#include "../PcfUeBindingBaseHandler.h"
#include "../../../Service/PcfUeBinding/IPcfUeBindingService.h"
#include "../../../Service/PcfUeBinding/PcfUeBindingServiceComponent.h"

#include "userver/components/component_context.hpp"


std::string PcfUeBindingPostHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest &request,
    userver::server::request::RequestContext &context) const {
    try {
        if (request.GetMethod() != userver::server::http::HttpMethod::kPost) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
            return R"({"error":"Method not allowed"})";
        }

        const auto& body = request.RequestBody();
        org::openapitools::server::model::PcfForUeBinding binding;
        binding.fromJsonString(body);

        auto uuid = m_service->Register(binding);

        const auto& host = request.GetHeader("Host");
        const std::string location = "http://" + host + "/nbsf-management/v1/pcf-ue-bindings/" + std::to_string(uuid);

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated);
        request.GetHttpResponse().SetHeader(std::string("Location"), location);

        return binding.toJsonString(true);
    } catch (const std::invalid_argument& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = e.what();
        throw userver::server::handlers::RequestParseError(error.ExtractValue());
    } catch (const std::exception& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = "Internal server error";
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}
