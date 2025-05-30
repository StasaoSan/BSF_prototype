#pragma once
#include <optional>
#include "gen/nbsf-management/model/PcfBinding.h"
#include "gen/nbsf-management/model/PcfForUeBinding.h"

class IPcfUeBindingDao {
public:
    virtual ~IPcfUeBindingDao() = default;

    virtual std::uint64_t Register(const org::openapitools::server::model::PcfForUeBinding& binding) = 0;
    virtual bool Delete(std::uint64_t) = 0;
    virtual std::vector<org::openapitools::server::model::PcfForUeBinding> FindBySupi(const std::string& supi) const = 0;
    virtual std::vector<org::openapitools::server::model::PcfForUeBinding> FindByGpsi(const std::string& gpsi) const = 0;
    virtual bool Exist(const org::openapitools::server::model::PcfForUeBinding& binding) const = 0;
};