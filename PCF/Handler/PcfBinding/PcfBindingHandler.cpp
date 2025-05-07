#include "PcfBindingHandler.h"

#include <iostream>

#include "../../../gen/model/PcfBinding.h"
#include "../../Service/PcfBinding/IPcfBindingService.h"
#include "userver/components/component_context.hpp"
#include "../../Service/PcfBinding/PcfBindingServiceComponent.h"

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
        if (request.GetMethod() == userver::server::http::HttpMethod::kPost) {
            const auto& body = request.RequestBody();
            org::openapitools::server::model::PcfBinding binding;
            binding.fromJsonString(body);

            const auto uuid = m_service->Register(binding);

            userver::formats::json::ValueBuilder response;
            response["uuid"] = uuid;

            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated); // created 200

            request.GetHttpResponse().SetHeader(
                std::string("Location"),
                "http://" + request.GetHeader("Host") + "/nbsf-management/v1/pcfBindings/" + std::to_string(uuid));
            return  binding.toJsonString(true); // json request. Can add uuid via: userver::formats::json::ToString(response.ExtractValue())
        }
        if (request.GetMethod() == userver::server::http::HttpMethod::kGet) {
            std::optional<org::openapitools::server::model::PcfBinding> binding_opt;

            const auto ipv4 = request.GetArg("ipv4Addr");
            const auto mac = request.GetArg("macAddr48");

            if (!ipv4.empty()) {
                binding_opt = m_service->FindByIpv4(ipv4);
            } else if (!mac.empty()) {
                binding_opt = m_service->FindByMac(mac);
            } else {
                request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNotFound);
                return R"({"error": "UE Address required (ipv4Addr or macAddr48"}
            )";
        }
        if (request.GetMethod() == userver::server::http::HttpMethod::kDelete) {
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
                return {};
            }
        }
        if (!binding_opt.has_value()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNotFound);
            return "";
        }

        const auto& binding = binding_opt.value();

        const auto supi = request.GetArg("supi");
        if (!supi.empty() && supi != binding.getSupi()) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return "";
        }

        const auto dnn = request.GetArg("dnn");
        const auto sst = request.GetArg("snssai.sst");
        const auto sd = request.GetArg("snssai.sd");

        if (!dnn.empty() && (dnn != binding.getDnn() ||
                             (!sst.empty() && std::stoi(sst) != binding.getSnssai().getSst()) ||
                             (!sd.empty() && sd != binding.getSnssai().getSd()))) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
            return "";
        }

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kOk);
        return binding.toJsonString(true);
    }
        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed); // unsupported method
        return "";
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