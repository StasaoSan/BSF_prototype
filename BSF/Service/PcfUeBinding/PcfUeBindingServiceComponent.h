#pragma once
#include "../../DAO/PcfUeBinding/InMemoryPcfUeBindingDao.h"
#include "userver/components/component_base.hpp"
#include "../../../UUID/UuidGenerator.h"
#include "IPcfUeBindingService.h"
#include "PcfUeBindingService.h"

class PcfUeBindingServiceComponent final: public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "pcf-ue-binding-service";
    PcfUeBindingServiceComponent(const userver::components::ComponentConfig& config,
                                 const userver::components::ComponentContext& context): ComponentBase(config, context) {
        auto dao = std::make_shared<InMemoryPcfUeBindingDao>(std::make_unique<UuidGenerator>());
        m_service = std::make_shared<PcfUeBindingService>(dao);
    }

    std::shared_ptr<IPcfUeBindingService> GetService(){
        return m_service;
    }

private:
    std::shared_ptr<IPcfUeBindingService> m_service;
};