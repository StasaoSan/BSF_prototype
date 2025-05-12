#pragma once
#include <string_view>
#include "userver/server/handlers/http_handler_base.hpp"

class IPcfBindingService;

class PcfBindingBaseHandler : public userver::server::handlers::HttpHandlerBase {
public:
    using HttpHandlerBase::HttpHandlerBase;

    explicit PcfBindingBaseHandler(const userver::components::ComponentConfig& config,
                                   const userver::components::ComponentContext& context);

protected:
    std::shared_ptr<IPcfBindingService> m_service;
};
