#include <string>
#include <iostream>
#include "InMemoryPcfBindingDao.h"
#include "../../../gen/model/PcfBinding.h"

std::uint64_t InMemoryPcfBindingDao::Register(org::openapitools::server::model::PcfBinding binding) {
    const auto uuid = uuidGenerator->Generate();
    uuidToPcfPath[uuid] = binding;
    if (!binding.getIpv4Addr().empty())
        ipv4ToUuid[binding.getIpv4Addr().data()] = uuid;

    if (!binding.getMacAddr48().empty())
        macToUuid[binding.getMacAddr48()] = uuid;
    std::cout <<"REGISTER START"<<std::endl;
    std::cout<<"UUID now: "<<uuid<<std::endl;
    std::cout<<"ALL UUIDs: " <<std::endl;
    for (const auto& [uuid, binding] : uuidToPcfPath) {
        std::cout << "Stored UUID: " << uuid << std::endl;
    }
    std::cout <<"REGISTER END"<<std::endl;
    return uuid;
}

bool InMemoryPcfBindingDao::Delete(std::uint64_t uuid) {
    std::cout <<"DELETE START"<<std::endl;
    for (const auto& [uuid, binding] : uuidToPcfPath) {
        std::cout << "Stored UUID: " << uuid << std::endl;
    }
    const auto it = uuidToPcfPath.find(uuid);
    if (it == uuidToPcfPath.end())
        return false;

    const auto& binding = it->second;
    RemoveUuidFromMap(ipv4ToUuid, binding.getIpv4Addr());
    RemoveUuidFromMap(macToUuid, binding.getMacAddr48());
    uuidToPcfPath.erase(it);
    std::cout <<"DELETE END"<<std::endl;
    return true;
}

std::optional<org::openapitools::server::model::PcfBinding> InMemoryPcfBindingDao::FindByMac(std::string mac) {
    return FindThroughtMap(macToUuid, mac, uuidToPcfPath);
}

std::optional<org::openapitools::server::model::PcfBinding> InMemoryPcfBindingDao::FindByIpv4(std::string ipv4) {
    return FindThroughtMap(ipv4ToUuid, ipv4, uuidToPcfPath);
}

template <typename Map, typename Key, typename Storage>
std::optional<typename Storage::mapped_type> InMemoryPcfBindingDao::FindThroughtMap(const Map& map, Key key, Storage& storage){
    if (const auto it = map.find(key); it != map.end()){
        const auto uuid = it->second;
        if (const auto res = storage.find(uuid); res != storage.end())
            return res->second;
    }
    return std::nullopt;
}

template <typename Map, typename Key>
void InMemoryPcfBindingDao::RemoveUuidFromMap(Map& map, const Key& key) {
    auto it = map.find(key);
    if (it != map.end()) {
        map.erase(it);
    }
}