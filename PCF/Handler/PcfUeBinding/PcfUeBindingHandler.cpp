#include "PcfUeBindingHandler.h"
#include "../../Service/PcfUeBinding/IPcfUeBindingService.h"
#include "../../Service/PcfUeBinding/PcfUeBindingServiceComponent.h"

#include "userver/components/component_context.hpp"

PcfUeBindingHandler::PcfUeBindingHandler(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context
) : HttpHandlerBase(config, context) {
    auto& service_component = context.FindComponent<PcfUeBindingServiceComponent>();
    m_service = service_component.GetService();
}

std::string PcfUeBindingHandler::HandleRequestThrow(
        const userver::server::http::HttpRequest& request,
        userver::server::request::RequestContext&
) const {
    try {
        if (request.GetMethod() == userver::server::http::HttpMethod::kPost) {
            const auto& body = request.RequestBody();
            org::openapitools::server::model::PcfForUeBinding binding;
            binding.fromJsonString(body);

            auto uuid = m_service->Register(binding);

            const auto& host = request.GetHeader("Host");
            const std::string location = "http://" + host + "/nbsf-management/v1/pcf-ue-bindings/" + std::to_string(uuid);
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kCreated);
            request.GetHttpResponse().SetHeader(std::string("Location"), location);
            return binding.toJsonString(true);
        }

        if (request.GetMethod() == userver::server::http::HttpMethod::kGet) {
            const auto& supi = request.GetArg("supi");
            const auto& gpsi = request.GetArg("gpsi");

            if (!supi.empty() && !gpsi.empty())
                throw std::invalid_argument("Only one of supi or gpsi must be provided");

            std::vector<org::openapitools::server::model::PcfForUeBinding> results;

            if (!supi.empty()) {
                results = m_service->FindBySupi(supi);
            } else if (!gpsi.empty()) {
                results = m_service->FindByGpsi(gpsi);
            } else {
                throw std::invalid_argument("Missing supi or gpsi");
            }

            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kOk);

            if (results.empty()) return "[]";

            userver::formats::json::ValueBuilder response;
            for (const auto& binding : results) {
                userver::formats::json::Value parsed_json = userver::formats::json::FromString(binding.toJsonString());
                response.PushBack(parsed_json);
            }
            return userver::formats::json::ToString(response.ExtractValue());
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
        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
        return "";

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