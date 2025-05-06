#pragma once

#include <string_view>
#include "userver/server/handlers/http_handler_base.hpp"

class IPcfUeBindingService;

class PcfUeBindingHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "pcf-ue-binding-handler";
    using HttpHandlerBase::HttpHandlerBase;

    PcfUeBindingHandler(const userver::components::ComponentConfig& config,
                        const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                   userver::server::request::RequestContext& context) const override;

private:
    std::shared_ptr<IPcfUeBindingService> m_service;
};