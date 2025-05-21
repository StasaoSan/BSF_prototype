#pragma once
#include <cstdint>
#include <optional>

#include "../../../gen/nbsf-management/model/PcfBinding.h"

class IPcfBindingService {
public:
    virtual ~IPcfBindingService() = default;

    virtual int64_t Register(const org::openapitools::server::model::PcfBinding& binding) = 0;
    virtual bool Delete(std::uint64_t uuid) = 0;
    virtual bool Exist(const org::openapitools::server::model::PcfBinding& binding) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByMac(std::string mac) = 0;
};
