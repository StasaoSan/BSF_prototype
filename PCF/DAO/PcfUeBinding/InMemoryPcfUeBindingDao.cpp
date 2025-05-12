#include "InMemoryPcfUeBindingDao.h"
#include <iostream>

std::uint64_t InMemoryPcfUeBindingDao::Register(const org::openapitools::server::model::PcfForUeBinding& binding) {
    std::uint64_t uuid = uuidGenerator->Generate();
    uuidToBinding[uuid] = binding;
    if (!binding.getSupi().empty())
        supiToUuid[binding.getSupi()].push_back(uuid);
    if (!binding.getGpsi().empty())
        gpsiToUuid[binding.getGpsi()].push_back(uuid);
    return uuid;
}

bool InMemoryPcfUeBindingDao::Delete(std::uint64_t uuid) {
    auto it = uuidToBinding.find(uuid);
    if (it == uuidToBinding.end())
        return false;

    const auto& binding = it->second;
    RemoveVecUuidFromMap(supiToUuid, binding.getSupi(), uuid);
    RemoveVecUuidFromMap(gpsiToUuid, binding.getGpsi(), uuid);
    uuidToBinding.erase(it);
    return true;
}

std::vector<org::openapitools::server::model::PcfForUeBinding> InMemoryPcfUeBindingDao::FindBySupi(const std::string& supi) const {
    return FindThroughtMap(supiToUuid, supi, uuidToBinding);
}

std::vector<org::openapitools::server::model::PcfForUeBinding> InMemoryPcfUeBindingDao::FindByGpsi(const std::string& gpsi) const {
    return FindThroughtMap(gpsiToUuid, gpsi, uuidToBinding);
}

template<typename mapToUuid, typename Key, typename StorageMap>
std::vector<typename StorageMap::mapped_type> InMemoryPcfUeBindingDao::FindThroughtMap(const mapToUuid map, const Key key, const StorageMap uuidToValue) const {
    std::vector<typename StorageMap::mapped_type> result;

    auto it = map.find(key);
    if (it == map.end()) return result;

    for (auto uuid : it->second) {
        auto value = uuidToValue.find(uuid);
        if (value != uuidToValue.end())
            result.push_back(value->second);
    }
    return result;
}

template <typename Map>
void InMemoryPcfUeBindingDao::RemoveVecUuidFromMap(Map& map, const std::string& key, std::uint64_t uuid){
    auto it = map.find(key);
    if (it != map.end()) {
        auto& vec = it->second;
        vec.erase(std::remove(vec.begin(), vec.end(), uuid), vec.end());
        if (vec.empty()) {
            map.erase(it);
        }
    }
}