#pragma once
#include <string>
#include "IPcfBindingDao.h"
#include "../UUID/UuidGenerator.h"

class InMemoryPcfBindingDao : public IPcfBindingDao {
public:
    explicit InMemoryPcfBindingDao() { std::unique_ptr<IUuidGenerator> uuid_generator = std::make_unique<UuidGenerator>(); };
    std::int64_t Register(org::openapitools::server::model::PcfBinding patch) override;

private:
    std::unordered_map<std::string, std::int64_t> ipv4ToUuid;
    std::unordered_map<std::int64_t, org::openapitools::server::model::PcfBinding> uuidToPcfPath;

    std::unique_ptr<IUuidGenerator> uuidGenerator;
};
