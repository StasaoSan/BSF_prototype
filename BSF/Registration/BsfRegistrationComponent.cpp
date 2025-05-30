#include "BsfRegistrationComponent.h"
#include <iostream>
#include <nlohmann/json.hpp>
#include <userver/logging/log.hpp>
#include <userver/yaml_config/schema.hpp>
#include "userver/utils/uuid4.hpp"
#include <userver/components/component_base.hpp>
#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <boost/property_tree/ptree.hpp>
#include "userver/clients/http/response.hpp"
#include "userver/clients/http/component.hpp"
#include <userver/yaml_config/merge_schemas.hpp>
#include "BsfRegistrationComponent.h"
#include <userver/yaml_config/merge_schemas.hpp>

std::pair<std::string,int> SplitHostPort(const std::string& addr, int def_port) {
    auto pos = addr.find(':');
    if (pos == std::string::npos) return {addr, def_port};
    return {addr.substr(0, pos), std::stoi(addr.substr(pos + 1))};
}

BsfRegistrationComponent::BsfRegistrationComponent(
        const userver::components::ComponentConfig& cfg,
        const userver::components::ComponentContext& ctx)
        : ComponentBase(cfg, ctx),
        m_http(ctx.FindComponent<userver::components::HttpClient>().GetHttpClient()),
        m_instanceId(userver::utils::generators::GenerateUuid()),
        m_port(7777),
        m_ipv4(cfg["ipv4"].As<std::string>("")),
        m_registered(false)
{
    const std::string scp = cfg["scp-address"].As<std::string>("");
    const std::string nrf = cfg["nrf-address"].As<std::string>("");

    if (scp.empty() && nrf.empty()) {
        std::cout << "NRF/SCP address not set – registration skipped" << std::endl;
        return;
    }

    auto hp = SplitHostPort(!scp.empty() ? scp : nrf, 7777);
    m_host = hp.first;
    m_port = hp.second;
}

void BsfRegistrationComponent::OnAllComponentsLoaded()
{
    if (!m_host.empty()) Register();
}

void BsfRegistrationComponent::OnAllComponentsAreStopping()
{
    Deregister();
}

void BsfRegistrationComponent::Register()
{
    nlohmann::json profile{
            {"nfInstanceId", m_instanceId},
            {"nfType",       "BSF"},
            {"nfStatus",     "REGISTERED"},
            {"ipv4Addresses",  nlohmann::json::array({m_ipv4})},
            {"allowedNfTypes",  nlohmann::json::array({"PCF","AF","SCP"})},
            {"priority", 0},
            {"capacity", 100},
            {"load", 0}
    };

    const std::string svc_id = userver::utils::generators::GenerateUuid();
    profile["nfServiceList"] = {
            { svc_id,
              {
                      {"serviceInstanceId", svc_id},
                      {"serviceName", "nbsf-management"},
                      {"versions",  nlohmann::json::array({ {{"apiVersionInUri","v1"},{"apiFullVersion","1.0.0"}} })},
                      {"scheme", "http"},
                      {"nfServiceStatus", "REGISTERED"},
                      {"ipEndPoints",  nlohmann::json::array({ {{"ipv4Address",m_ipv4}, {"port",m_port}} })}
              }
            }
    };

    const std::string url = "http://" + m_host + ":"
                            + std::to_string(m_port)
                            + "/nnrf-nfm/v1/nf-instances/" + m_instanceId;
    try {
        auto resp = m_http.CreateRequest()
                .put(url, profile.dump())
                .timeout(std::chrono::seconds{5})
                .perform();

        auto code = resp->status_code();
        if (code != userver::clients::http::Status::OK && code != userver::clients::http::Status::Created)
            throw std::runtime_error("BSF registration failed: HTTP " + std::to_string(code));
        m_registered = true;
        std::cout << "BSF registered at " << url << " (HTTP " << code << ")"  << std::endl;;
    } catch (const std::exception &e) {
        std::cerr << "BSF registration failed: "  << e.what() << std::endl;
    }
}

void BsfRegistrationComponent::Deregister() noexcept
{

}
userver::yaml_config::Schema
BsfRegistrationComponent::GetStaticConfigSchema() {
    constexpr auto kSchemaYAML = R"(
type: object
description: "BSF-registration in NRF/SCP"
additionalProperties: false
properties:
  nrf-address:
    type: string
    description: "host[:port] NRF"
  scp-address:
    type: string
    description: "host[:port] SCP - override NRF"
  ipv4:
    type: string
    description: "local IPv4 BSF"
    )";
    return userver::yaml_config::MergeSchemas<userver::components::ComponentBase>(
            kSchemaYAML);
}