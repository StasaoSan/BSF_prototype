#pragma once
#include "../PcfUeBindingBaseHandler.h"

class PcfUeBindingGetHandler final : public PcfUeBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-ue-binding-get";
    using PcfUeBindingBaseHandler::PcfUeBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest &request,
        userver::server::request::RequestContext &context) const override;
};