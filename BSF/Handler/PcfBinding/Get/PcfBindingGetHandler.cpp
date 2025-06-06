//
// Created by Тихонов Александр on 08.05.2025.
//
#include <iostream>
#include "PcfBindingGetHandler.h"
#include "gen/nbsf-management/model/PcfBinding.h"
#include "userver/components/component_context.hpp"
#include "BSF/Service/PcfBinding/IPcfBindingService.h"
#include "BSF/Service/PcfBinding/PcfBindingServiceComponent.h"

std::string PcfBindingGetHandler::HandleRequestThrow(
        const userver::server::http::HttpRequest &request,
        userver::server::request::RequestContext &) const {
    try {
        if (request.GetMethod() != userver::server::http::HttpMethod::kGet) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
            return R"({"error":"Method not allowed"})";
        }

        const auto ipv4 = request.GetArg("ipv4Addr");
        const auto mac = request.GetArg("macAddr48");

        if (ipv4.empty() && mac.empty()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kBadRequest);
            return R"({"error":"At least one of 'ipv4Addr' or 'macAddr48' is required"})";
        }

        std::optional<org::openapitools::server::model::PcfBinding> byIpv4;
        std::optional<org::openapitools::server::model::PcfBinding> byMac;

        byIpv4 = !ipv4.empty() ? m_service->FindByIpv4(ipv4) : std::nullopt;
        byMac = !mac.empty() ? m_service->FindByMac(mac) : std::nullopt;

        if (byIpv4 && byMac && byIpv4->getPcfId() != byMac->getPcfId()) { // 400 bad req
            userver::formats::json::ValueBuilder err;
            err["error"]   = "MULTIPLE_BINDING_INFO_FOUND";
            throw userver::server::handlers::ClientError(err.ExtractValue());
        }

        auto binding_opt = byIpv4.has_value() ? byIpv4 : byMac;

        if (!binding_opt.has_value()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNotFound);
            return R"({"error":"Binding not found"})";
        }

        const auto& binding = binding_opt.value();

        const auto supi = request.GetArg("supi");
        if (!supi.empty() && supi != binding.getSupi()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return {};
        }

        const auto dnn = request.GetArg("dnn");
        const auto sst = request.GetArg("snssai.sst");
        const auto sd = request.GetArg("snssai.sd");

        const bool dnn_mismatch = !dnn.empty() && dnn != binding.getDnn();
        const bool sst_mismatch = !sst.empty() && std::stoi(sst) != binding.getSnssai().getSst();
        const bool sd_mismatch  = !sd.empty()  && sd  != binding.getSnssai().getSd();

        if (dnn_mismatch || sst_mismatch || sd_mismatch) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return {};
        }

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kOk);
        return binding.toJsonString(true);

    } catch (const std::invalid_argument &e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = e.what();
        std::cerr << "Validation failed: " << e.what() << std::endl;
        throw userver::server::handlers::RequestParseError(error.ExtractValue());
    } catch (const userver::server::handlers::RequestParseError&) {
        throw;
    } catch (const std::exception &e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = "Internal service error";
        error["details"] = e.what();
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}