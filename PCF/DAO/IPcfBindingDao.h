#pragma once
#include "../../gen/model/PcfBinding.h"
#include <optional>
class IPcfBindingDao {
public:
    virtual ~IPcfBindingDao() = default;

    virtual std::int64_t Register(org::openapitools::server::model::PcfBinding binding) = 0;
    virtual std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) = 0;
};