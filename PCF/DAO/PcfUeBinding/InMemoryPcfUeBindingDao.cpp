#include "InMemoryPcfUeBindingDao.h"

std::uint64_t InMemoryPcfUeBindingDao::Register(const org::openapitools::server::model::PcfForUeBinding& binding) {
    std::uint64_t uuid = uuidGenerator->Generate();
    uuidToBinding[uuid] =
            binding;

    const std::string &supi = binding.getSupi();
    if (!supi.empty())
        supiToUuid[supi].push_back(uuid);

    const std::string &gpsi = binding.getGpsi();
    if (!gpsi.empty())
        gpsiToUuid[gpsi].push_back(uuid);
    return uuid;
}

std::vector<org::openapitools::server::model::PcfForUeBinding> InMemoryPcfUeBindingDao::FindBySupi(const std::string& supi) const {
    std::vector<org::openapitools::server::model::PcfForUeBinding> result;
    auto it = supiToUuid.find(supi);
    if (it != supiToUuid.end()) {
        for (const auto &uuid: it->second) {
            auto found = uuidToBinding.find(uuid);
            if (found != uuidToBinding.end()) {
                result.push_back(found->second);
            }
        }
    }
    return result;
}

std::vector<org::openapitools::server::model::PcfForUeBinding> InMemoryPcfUeBindingDao::FindByGpsi(const std::string& gpsi) const {
    std::vector<org::openapitools::server::model::PcfForUeBinding> result;
    auto it = gpsiToUuid.find(gpsi);
    if (it != gpsiToUuid.end()) {
        for (const auto &uuid: it->second) {
            auto found = uuidToBinding.find(uuid);
            if (found != uuidToBinding.end()) {
                result.push_back(found->second);
            }
        }
    }
    return result;
}