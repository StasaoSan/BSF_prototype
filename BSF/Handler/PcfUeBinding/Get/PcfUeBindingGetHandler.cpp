#include "PcfUeBindingGetHandler.h"
#include "../PcfUeBindingBaseHandler.h"
#include "../../../Service/PcfUeBinding/IPcfUeBindingService.h"
#include "../../../Service/PcfUeBinding/PcfUeBindingServiceComponent.h"

#include "userver/components/component_context.hpp"

std::string PcfUeBindingGetHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest &request,
    userver::server::request::RequestContext &context) const {
    try {
        if (request.GetMethod() != userver::server::http::HttpMethod::kGet) {
            request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kMethodNotAllowed);
            return R"({"error":"Method not allowed"})";
        }

        const auto& supi = request.GetArg("supi");
        const auto& gpsi = request.GetArg("gpsi");

        if (!supi.empty() && !gpsi.empty())
            throw std::invalid_argument("Only one of supi or gpsi must be provided");

        std::vector<org::openapitools::server::model::PcfForUeBinding> results;

        if (!supi.empty())
            results = m_service->FindBySupi(supi);
        else if (!gpsi.empty())
            results = m_service->FindByGpsi(gpsi);
        else
            throw std::invalid_argument("Missing supi or gpsi");

        if (results.size() > 1) { // 400 Bad Req
            userver::formats::json::ValueBuilder error;
            error["error"]   = "MULTIPLE_BINDING_INFO_FOUND";
            throw userver::server::handlers::ClientError(error.ExtractValue());
        }

        request.GetHttpResponse().SetStatus(userver::server::http::HttpStatus::kOk);

        if (results.empty()) return "[]";

        userver::formats::json::ValueBuilder response;
        for (const auto& binding : results) {
            userver::formats::json::Value parsed_json = userver::formats::json::FromString(binding.toJsonString());
            response.PushBack(parsed_json);
        }
        return userver::formats::json::ToString(response.ExtractValue());
    } catch (const std::invalid_argument& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = e.what();
        throw userver::server::handlers::RequestParseError(error.ExtractValue());
    } catch (const userver::server::handlers::RequestParseError&) {
        throw;
    } catch (const std::exception& e) {
        userver::formats::json::ValueBuilder error;
        error["message"] = "Internal server error";
        throw userver::server::handlers::InternalServerError(error.ExtractValue());
    }
}
