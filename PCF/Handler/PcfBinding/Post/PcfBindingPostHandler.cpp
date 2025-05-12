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

        const auto uuid = m_service->Register(binding);

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated);

        request.GetHttpResponse().SetHeader(
                std::string("Location"),
                "http://" + request.GetHeader("Host") + "/nbsf-management/v1/pcfBindings/" + std::to_string(uuid)
        );

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