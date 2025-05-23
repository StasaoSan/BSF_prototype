#pragma once
#include "IPcfUeBindingService.h"
#include "../../DAO/PcfUeBinding/IPcfUeBindingDao.h"

class PcfUeBindingService : public IPcfUeBindingService {
public:
    explicit PcfUeBindingService(std::shared_ptr<IPcfUeBindingDao> dao);

    std::uint64_t Register(const org::openapitools::server::model::PcfForUeBinding& binding) override;
    bool Delete(std::uint64_t uuid) override;
    bool Exist(const org::openapitools::server::model::PcfForUeBinding &binding) override;
    std::vector<org::openapitools::server::model::PcfForUeBinding> FindBySupi(const std::string& supi) const override;
    std::vector<org::openapitools::server::model::PcfForUeBinding> FindByGpsi(const std::string& gpsi) const override;
private:
    static void Validate(const org::openapitools::server::model::PcfForUeBinding& binding);

    std::shared_ptr<IPcfUeBindingDao> m_dao;
    static bool isValidSupi(const std::string& supi);
    static bool isValidGpsi(const std::string& gpsi);
    static bool isValidFqdn(const std::string& fqdn);
    static bool isValidEndpoint(const org::openapitools::server::model::IpEndPoint& endpoint);
    static bool isValidIpv4(const std::string& ipAddr);
};