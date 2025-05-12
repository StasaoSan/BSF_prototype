#pragma once

#include <string_view>
#include "userver/server/handlers/http_handler_base.hpp"

class IPcfUeBindingService;

class PcfUeBindingBaseHandler : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "pcf-ue-binding-handler";
    using HttpHandlerBase::HttpHandlerBase;

    PcfUeBindingBaseHandler(const userver::components::ComponentConfig& config,
                            const userver::components::ComponentContext& context);
private:
    std::shared_ptr<IPcfUeBindingService> m_service;
};