//
// Created by Тихонов Александр on 10.05.2025.
//
#include "PcfUeBindingDeleteHandler.h"
#include "../PcfUeBindingBaseHandler.h"
#include "userver/components/component_context.hpp"
#include "../../../Service/PcfUeBinding/IPcfUeBindingService.h"
#include "../../../Service/PcfUeBinding/PcfUeBindingServiceComponent.h"

std::string PcfUeBindingDeleteHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest &request,
    userver::server::request::RequestContext &context) const {
    try {
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

        if (m_service->Delete(id)) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return {};
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
        error["message"] = "Internal server error";
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}
