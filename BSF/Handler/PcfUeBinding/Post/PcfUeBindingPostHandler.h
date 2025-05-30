#pragma once
#include "BSF/Handler/PcfUeBinding/PcfUeBindingBaseHandler.h"

class PcfUeBindingPostHandler final : public PcfUeBindingBaseHandler {
public:
    static constexpr std::string_view kName = "pcf-ue-binding-post";
    using PcfUeBindingBaseHandler::PcfUeBindingBaseHandler;

    std::string HandleRequestThrow(const userver::server::http::HttpRequest &request,
        userver::server::request::RequestContext &context) const override;
};