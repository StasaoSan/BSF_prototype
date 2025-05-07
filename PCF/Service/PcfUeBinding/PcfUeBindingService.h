#pragma once
#include "IPcfUeBindingService.h"
#include "../../DAO/PcfUeBinding/IPcfUeBindingDao.h"

class PcfUeBindingService : public IPcfUeBindingService {
public:
    explicit PcfUeBindingService(std::shared_ptr<IPcfUeBindingDao> dao);

    std::uint64_t Register(const org::openapitools::server::model::PcfForUeBinding& binding) override;
    bool Delete(std::uint64_t uuid) override;
    std::vector<org::openapitools::server::model::PcfForUeBinding> FindBySupi(const std::string& supi) const override;
    std::vector<org::openapitools::server::model::PcfForUeBinding> FindByGpsi(const std::string& gpsi) const override;
private:
    std::shared_ptr<IPcfUeBindingDao> m_dao;
    // Validate ??
};