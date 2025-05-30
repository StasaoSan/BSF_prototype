#pragma once

#include "BSF/Handler/PcfBinding/PcfBindingBaseHandler.h"

class PcfBindingDeleteHandler final : public PcfBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-binding-delete";
    using PcfBindingBaseHandler::PcfBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest& request,
                                   userver::server::request::RequestContext& context) const override;
};
