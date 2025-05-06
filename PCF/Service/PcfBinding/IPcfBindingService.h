#pragma once
#include <cstdint>
#include <optional>

#include "../../../gen/model/PcfBinding.h"

class IPcfBindingService {
public:
    virtual ~IPcfBindingService() = default;

    virtual int64_t Register(org::openapitools::server::model::PcfBinding binding) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByMac(std::string mac) = 0;
};
