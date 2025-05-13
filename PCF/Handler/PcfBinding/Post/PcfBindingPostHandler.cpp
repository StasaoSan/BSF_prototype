#include <iostream>
#include "PcfBindingPostHandler.h"
#include "../../../gen/model/PcfBinding.h"
#include "userver/components/component_context.hpp"
#include "../../../Service/PcfBinding/IPcfBindingService.h"
#include "../../../Service/PcfBinding/PcfBindingServiceComponent.h"

std::string PcfBindingPostHandler::HandleRequestThrow(
        const userver::server::http::HttpRequest &request,
        userver::server::request::RequestContext &) const {
    try {
        if (request.GetMethod() != userver::server::http::HttpMethod::kPost) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
            return R"({"error":"Method not allowed"})";
        }

        const auto& body = request.RequestBody();

        org::openapitools::server::model::PcfBinding binding;
        try {
            binding.fromJsonString(body);
        } catch (const std::exception& e) {
            userver::formats::json::ValueBuilder error;
            error["message"] = std::string("Invalid JSON: ") + e.what();
            throw userver::server::handlers::RequestParseError(error.ExtractValue());
        }

        if (m_service->Exist(binding)) { // 403 Forbidden
            userver::formats::json::ValueBuilder error;
            error["error"] = "EXISTING_BINDING_INFO_FOUND";

            throw userver::server::handlers::CustomHandlerException(
                userver::server::handlers::HandlerErrorCode::kForbidden,
                error.ExtractValue());
        }

        const auto uuid = m_service->Register(binding);
        const std::string location = "http://" + request.GetHeader("Host") + "/nbsf-management/v1/pcfBindings/" + std::to_string(uuid);

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated);

        request.GetHttpResponse().SetHeader(
                std::string("Location"), location);

        userver::formats::json::ValueBuilder response;
        response["uuid"] = uuid;
        return binding.toJsonString(true);
    } catch (const userver::server::handlers::RequestParseError&) {
        throw;
    } catch (const std::invalid_argument& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = e.what();
        throw userver::server::handlers::RequestParseError(error.ExtractValue());
    } catch (const std::exception& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = "Internal service error";
        error["details"] = e.what();
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}