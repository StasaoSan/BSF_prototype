#pragma once

#include <string_view>
#include "userver/server/handlers/http_handler_base.hpp"

class IPcfUeBindingService;

class PcfUeBindingBaseHandler : public userver::server::handlers::HttpHandlerBase {
public:
    using HttpHandlerBase::HttpHandlerBase;

    explicit PcfUeBindingBaseHandler(const userver::components::ComponentConfig& config,
                                     const userver::components::ComponentContext& context);
protected:
    std::shared_ptr<IPcfUeBindingService> m_service;
};