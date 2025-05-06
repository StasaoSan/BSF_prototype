#pragma once
#include "IPcfUeBindingDao.h"
#include "../../../UUID/IUuidGenerator.h"
#include "../../../gen/model/PcfForUeBinding.h"

class InMemoryPcfUeBindingDao : public IPcfUeBindingDao {
public:
    explicit InMemoryPcfUeBindingDao(std::unique_ptr<IUuidGenerator> generator)
            : uuidGenerator(std::move(generator)) {}

    std::uint64_t Register(const org::openapitools::server::model::PcfForUeBinding& binding) override;

    std::vector<org::openapitools::server::model::PcfForUeBinding> FindBySupi(const std::string& supi) const override;

    std::vector<org::openapitools::server::model::PcfForUeBinding> FindByGpsi(const std::string& gpsi) const override;
private:
    std::unordered_map<std::string, std::vector<std::uint64_t>> supiToUuid;
    std::unordered_map<std::string, std::vector<std::uint64_t>> gpsiToUuid;
    std::unordered_map<std::uint64_t, org::openapitools::server::model::PcfForUeBinding> uuidToBinding;
    std::unique_ptr<IUuidGenerator> uuidGenerator;
};
