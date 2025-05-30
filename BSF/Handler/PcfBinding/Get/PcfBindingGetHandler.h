#pragma once
#include "BSF/Handler/PcfBinding/PcfBindingBaseHandler.h"

class PcfBindingGetHandler final : public PcfBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-binding-get";
    using PcfBindingBaseHandler::PcfBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                   userver::server::request::RequestContext& context) const override;
};
