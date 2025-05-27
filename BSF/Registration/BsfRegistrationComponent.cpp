////
//// Created by tikhonov-a on 5/20/25.
////
#include <iostream>
#include "BsfRegistrationComponent.h"
#include "userver/utils/uuid4.hpp"
#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/clients/http/request.hpp>
#include "userver/yaml_config/schema.hpp"
#include <boost/property_tree/ptree.hpp>
#include "userver/clients/http/response.hpp"
#include "userver/clients/http/client.hpp"
#include "userver/components/component_context.hpp"
#include "CppRestOpenAPIClient/model/NFProfile.h"
#include "CppRestOpenAPIClient/model/NFType.h"
#include "CppRestOpenAPIClient/model/NFStatus.h"
#include "CppRestOpenAPIClient/model/NFService.h"
#include "CppRestOpenAPIClient/model/NFServiceVersion.h"
#include "CppRestOpenAPIClient/model/IpEndPoint.h"

BsfRegistrationComponent::BsfRegistrationComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : userver::components::ComponentBase(config, context),
          m_http(context.FindComponent<userver::components::HttpClient>().GetHttpClient()),
          m_instance_id(userver::utils::generators::GenerateUuid())
{
    const std::string scp = config["scp-address"].As<std::string>("");
    const std::string nrf = config["nrf-address"].As<std::string>("");

    if (scp.empty() && nrf.empty()) {
        std::cerr << "NRF/SCP not found - register skipped" << std::endl;
        return;
    }

    RegisterSelf(!scp.empty() ? scp : nrf);
}

void BsfRegistrationComponent::RegisterSelf(const std::string& host) {
    using namespace org::openapitools::client::model;

    NFProfile profile;
    profile.setNfInstanceId(utility::conversions::to_string_t(m_instance_id));

    auto nfType = std::make_shared<NFType>();
    nfType->fromJson(web::json::value::string("BSF"));
    profile.setNfType(nfType);

    auto status = std::make_shared<NFStatus>();
    status->fromJson(web::json::value::string("REGISTERED"));
    profile.setNfStatus(status);

    const std::string body = utility::conversions::to_utf8string(profile.toJson().serialize());
    const std::string url = "http://" + host + "/nnrf-nfm/v1/nf-instances/" + m_instance_id;

    auto request_result = m_http.CreateRequest()
            .url(url)
            .put(body, "application/json")
            .perform();

    const auto status_code = request_result->status_code();

    if (status_code != userver::clients::http::Status::OK &&
        status_code != userver::clients::http::Status::Created) {
        throw std::runtime_error("NF registration failed, code " +
                                 std::to_string(status_code));
    }

    std::cout << "BSF successfully registered to NRF/SCP at: " << url;
}
