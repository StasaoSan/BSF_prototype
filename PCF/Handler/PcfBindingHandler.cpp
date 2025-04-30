#include "PcfBindingHandler.h"

#include <iostream>

#include "../../gen/model/PcfBinding.h"
#include "../Service/IPcfBindingService.h"
#include "userver/components/component_context.hpp"
#include "../Service/PcfBindingServiceComponent.h"

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
            const auto ipv4 = request.GetArg("ipv4Addr");
            const auto mac = request.GetArg("macAddr48");

            const auto supi = request.GetArg("supi");
            const auto dnn = request.GetArg("dnn");
            const auto sst = request.GetArg("snssai.sst");
            const auto sd = request.GetArg("snssai.sd");

            if (ipv4.empty() && mac.empty()) {
                throw std::invalid_argument("At least one UE Address (ipv4Addr or macAddr48) must be provided");
            }

            if (dnn.empty() || sst.empty()) {
                throw std::invalid_argument("dnn and snssai.sst are required");
            }

            std::optional<org::openapitools::server::model::PcfBinding> binding_opt;

            if (!ipv4.empty()) {
                binding_opt = m_service->FindByIpv4(ipv4);
            } else {
                binding_opt = m_service->FindByMac(mac);
            }

            if (!binding_opt.has_value()) {
                request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNotFound);
                return "";
            }

            const auto& binding = binding_opt.value();

            if (!supi.empty() && supi != binding.getSupi()) {
                request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
                return "";
            }

            if (dnn != binding.getDnn()) {
                request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
                return "";
            }

            const auto& snssai = binding.getSnssai();
            if (snssai.getSst() != std::stoi(sst)) {
                request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kNoContent);
                return "";
            }

            if (!sd.empty() && snssai.getSd() != sd) {
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
