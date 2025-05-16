#pragma once
#include "../PcfBindingBaseHandler.h"

class PcfBindingGetHandler final : public PcfBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-binding-get";
    using PcfBindingBaseHandler::PcfBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                   userver::server::request::RequestContext& context) const override;
};
