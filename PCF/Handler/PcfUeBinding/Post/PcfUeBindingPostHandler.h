#pragma once
#include "../PcfUeBindingBaseHandler.h"

class PcfBindingPostHandler final : public PcfUeBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-binding-post";
    using PcfUeBindingBaseHandler::PcfUeBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                   userver::server::request::RequestContext& context) const override;
};
