#pragma once

#include <memory>
#include <string>
#include <userver/clients/http/component.hpp>
#include <userver/components/component_base.hpp>
#include <userver/utils/uuid4.hpp>

class BsfRegistrationComponent final : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "bsf-reg";

    BsfRegistrationComponent(const userver::components::ComponentConfig& cfg,
                             const userver::components::ComponentContext& ctx);

    static userver::yaml_config::Schema GetStaticConfigSchema();

    struct Config {
        std::string nrf_address;
        std::string scpAddress;
    };

    void OnAllComponentsLoaded() override;
    void OnAllComponentsAreStopping() override;

private:
    void Register();
    void Deregister() noexcept;

    userver::clients::http::Client& m_http;
    std::string m_instanceId;
    std::string m_host;
    int m_port;
    std::string m_ipv4;
    bool m_registered;
};