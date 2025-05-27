#pragma once

#include <memory>
#include <string>

#include "userver/components/component_base.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/utils/uuid4.hpp"

#include "CppRestOpenAPIClient/model/NFProfile.h"
#include "CppRestOpenAPIClient/model/NFType.h"
#include "CppRestOpenAPIClient/model/NFStatus.h"
#include "CppRestOpenAPIClient/model/NFService.h"
#include "CppRestOpenAPIClient/model/NFServiceVersion.h"
#include "CppRestOpenAPIClient/model/IpEndPoint.h"

class BsfRegistrationComponent final : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "bsf-registration";

    BsfRegistrationComponent(const userver::components::ComponentConfig& config,
                             const userver::components::ComponentContext& context);

private:
    void RegisterSelf(const std::string& host);          // PUT /nnrf-nfm/…
    userver::clients::http::Client& m_http;
    std::string m_instance_id;                            // GUID v4
};
