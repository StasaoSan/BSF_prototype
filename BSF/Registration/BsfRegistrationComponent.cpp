//
// Created by tikhonov-a on 5/20/25.
//
#include <iostream>
#include "BsfRegistrationComponent.h"
#include "userver/utils/uuid4.hpp"
#include <userver/components/component_base.hpp>
#include "userver/yaml_config/schema.hpp"

BsfRegistrationComponent::BsfRegistrationComponent(
        const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context)
        : userver::components::ComponentBase(config, context),
          m_http(context.FindComponent<userver::components::HttpClient>().Get()),
          m_instance_id(userver::utils::generators::GenerateUuid())
{
    const std::string scp = config.HasMember("scp-adress") ? config["scp-address"].As<std::string>("") : "";
    const std::string nrf = config["nrf-address"].As<std::string>("");

    if (scp.empty() && nrf.empty()) {
        std::cerr <<"NRF/SCP адреса не заданы – регистрация пропущена" << std::endl;
        return; // model A - register not needed
    }

    RegisterSelf(!scp.empty() ? scp : nrf);
}

void BsfRegistrationComponent::RegisterSelf(const std::string& host)
{
    org::openapitools::client::model::NFProfile profile;
    profile.setNfInstanceId(m_instance_id);
    profile.setNfType(org::openapitools::client::model::NFType::BSF);
    profile.setNfStatus(org::openapitools::client::model::NFStatus::REGISTERED);

    const std::string body = profile.toJson();

    const std::string url =
            "http://" + host + "/nnrf-nfm/v1/nf-instances/" + m_instance_id;

    auto resp = m_http->CreateRequest()
            .url(url)
            .put(body, "application/json");

    if (resp->status_code() != 200 && resp->status_code() != 201) {
        throw std::runtime_error("NF registration failed, code "
                                 + std::to_string(resp->status_code()));
    }
}