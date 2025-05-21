//#pragma once
//
//#include <memory>
//#include <userver/clients/http/component.hpp>
//#include <userver/components/component_base.hpp>
//#include "../../gen/include/org.openapitools.server.model/model/NFProfile.h"
//
//
//class BsfRegistrationComponent final : public userver::components::ComponentBase {
//public:
//    static constexpr std::string_view kName = "bsf-registration";
//
//    BsfRegistrationComponent(const userver::components::ComponentConfig& cfg,
//                             const userver::components::ComponentContext& ctx);
//
//    static userver::yaml_config::Schema GetStaticConfigSchema();
//
//private:
//    void RegisterSelf(const std::string& host);          // PUT /nnrf-nfm/…
//    std::shared_ptr<userver::clients::http::Client> m_http;
//    std::string m_instance_id;                            // GUID v4
//};

#pragma once

#include <memory>
#include <string>

#include "userver/components/component_base.hpp"
#include "userver/clients/http/component.hpp"
#include "userver/utils/uuid4.hpp"

#include "../../gen/nrm-nfm/model/NFProfile.h"
#include "../../gen/nrm-nfm/model/NFType.h"
#include "../../gen/nrm-nfm/model/NFStatus.h"
#include "../../gen/nrm-nfm/model/NFService.h"
#include "../../gen/nrm-nfm/model/NFServiceVersion.h"
#include "../../gen/nrm-nfm/model/IpEndPoint.h"

class BsfRegistrationComponent final : public userver::components::ComponentBase {
public:
    static constexpr std::string_view kName = "bsf-registration";

    BsfRegistrationComponent(const userver::components::ComponentConfig& config,
                             const userver::components::ComponentContext& context);

private:
    void RegisterSelf(const std::string& host);          // PUT /nnrf-nfm/…
    std::shared_ptr<userver::clients::http::Client> m_http;
    std::string m_instance_id;                            // GUID v4
};
