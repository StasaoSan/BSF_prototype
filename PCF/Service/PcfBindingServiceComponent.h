#pragma once
#include "PcfBindingService.h"
#include "../DAO/InMemoryPcfBindingDao.h"
#include "userver/components/component_base.hpp"

class PcfBindingServiceComponent final : public userver::components::ComponentBase{
public:
    static constexpr std::string_view kName = "pcf-binding-service";
    PcfBindingServiceComponent(const userver::components::ComponentConfig& config,
        const userver::components::ComponentContext& context): ComponentBase(config, context) {
        auto dao = std::make_shared<InMemoryPcfBindingDao>(std::make_unique<UuidGenerator>());
        m_service = std::make_shared<PcfBindingService>(dao);
    }

    std::shared_ptr<IPcfBindingService> GetService() {
        return m_service;
    }
private:
    std::shared_ptr<IPcfBindingService> m_service;
};
