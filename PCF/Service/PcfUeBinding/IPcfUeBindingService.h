#pragma once
#include <optional>
#include "../../../gen/model/PcfBinding.h"
#include "../../../gen/model/PcfForUeBinding.h"

class IPcfUeBindingService{
public:
    virtual ~IPcfUeBindingService() = default;

    virtual std::uint64_t Register(const org::openapitools::server::model::PcfForUeBinding& binding) = 0;
    virtual bool Delete(std::uint64_t uuid) = 0;
    virtual std::vector<org::openapitools::server::model::PcfForUeBinding> FindBySupi(const std::string& supi) const = 0;
    virtual std::vector<org::openapitools::server::model::PcfForUeBinding> FindByGpsi(const std::string& gpsi) const = 0;
};