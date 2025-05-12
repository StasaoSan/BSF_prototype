#include <iostream>
#include "PcfBindingDeleteHandler.h"
#include "../../../gen/model/PcfBinding.h"
#include "userver/components/component_context.hpp"
#include "../../../Service/PcfBinding/IPcfBindingService.h"
#include "../../../Service/PcfBinding/PcfBindingServiceComponent.h"

std::string PcfBindingDeleteHandler::HandleRequestThrow( const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&) const {
    try {
        if (request.GetMethod() != userver::server::http::HttpMethod::kDelete) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
            return R"({"error":"Method not allowed"})";
        }

        const std::string& path = request.GetUrl();
        const auto pos = path.find_last_of('/');
        if (pos == std::string::npos || pos + 1 >= path.size()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kBadRequest);
            return R"({"error":"bindingId required"})";
        }

        const std::string id_str = path.substr(pos + 1);
        std::uint64_t id{};
        try {
            id = std::stoull(id_str);
        } catch (...) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kBadRequest);
            return R"({"error":"bindingId must be uint64"})";
        }

        const bool deleted = m_service->Delete(id);

        if (deleted) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return {};  // 204 No Content
        } else {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNotFound);
            return R"({"error":"bindingId not found"})";
        }

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
