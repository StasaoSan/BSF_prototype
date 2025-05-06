#pragma once
#include <string>
#include "IPcfBindingDao.h"
#include "../../../UUID/UuidGenerator.h"

class InMemoryPcfBindingDao : public IPcfBindingDao {
public:
    explicit InMemoryPcfBindingDao() {
        std::unique_ptr<IUuidGenerator> uuid_generator = std::make_unique<UuidGenerator>();
    };

    explicit InMemoryPcfBindingDao(std::unique_ptr<IUuidGenerator> generator)
        : uuidGenerator(std::move(generator)) {}

    std::uint64_t Register(org::openapitools::server::model::PcfBinding binding) override;
    std::optional<org::openapitools::server::model::PcfBinding> FindByIpv4(std::string ipv4) override;
    std::optional<org::openapitools::server::model::PcfBinding> FindByMac(std::string mac) override;

private:
    std::unordered_map<std::string, std::uint64_t> macToUuid;
    std::unordered_map<std::string, std::uint64_t> ipv4ToUuid;
    std::unordered_map<std::uint64_t, org::openapitools::server::model::PcfBinding> uuidToPcfPath;

    std::unique_ptr<IUuidGenerator> uuidGenerator;
};
