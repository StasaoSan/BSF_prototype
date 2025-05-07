#pragma once
#include <string_view>
#include "userver/server/handlers/http_handler_base.hpp"
//#include <userver/server/handlers/http_handler_json_base.hpp>

class IPcfBindingService;

class PcfBindingHandler final : public userver::server::handlers::HttpHandlerBase {
public:
    static constexpr std::string_view kName = "pcf-binding-handler";
    using HttpHandlerBase::HttpHandlerBase;
//    using HttpHandlerJsonBase::HttpHandlerJsonBase;

    explicit PcfBindingHandler(const userver::components::ComponentConfig& config,
                                const userver::components::ComponentContext& context);

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                    userver::server::request::RequestContext& context) const override;
//    userver::formats::json::Value HandleRequestJsonThrow(
//            const userver::server::http::HttpRequest& request,
//            const userver::formats::json::Value& request_json,
//            userver::server::request::RequestContext& ctx) const override;

private:
    std::shared_ptr<IPcfBindingService> m_service;
};
