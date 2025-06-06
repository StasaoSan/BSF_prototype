#pragma once
#include "IPcfBindingService.h"
#include "../../DAO/PcfBinding/IPcfBindingDao.h"

class PcfBindingService : public IPcfBindingService {
public:
    explicit PcfBindingService(const std::shared_ptr<IPcfBindingDao>& dao);

    int64_t Register(const org::openapitools::server::model::PcfBinding& binding) override;
    bool Delete(std::uint64_t uuid) override;
    bool Exist(const org::openapitools::server::model::PcfBinding &binding) override;
    std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) override;
    std::optional<org::openapitools::server::model::PcfBinding> FindByMac(std::string ipv4) override;
private:
    static void Validate(const org::openapitools::server::model::PcfBinding& binding);

    std::shared_ptr<IPcfBindingDao> m_dao;

    static bool isValidIPv4(const std::string &ipv4);
    static bool isValidIPv6(const std::string& ipv6);
    static bool isValidMac(const std::string& mac);
};
