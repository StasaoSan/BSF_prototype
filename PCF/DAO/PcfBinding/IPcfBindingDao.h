#pragma once
#include "../../../gen/model/PcfBinding.h"
#include <optional>
class IPcfBindingDao {
public:
    virtual ~IPcfBindingDao() = default;

    virtual std::uint64_t Register(org::openapitools::server::model::PcfBinding binding) = 0;
    virtual bool Delete(std::uint64_t) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByMac(std::string mac) = 0;
};