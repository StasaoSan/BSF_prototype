#include <string>
#include "InMemoryPcfBindingDao.h"
#include "../../gen/model/PcfBinding.h"

std::uint64_t InMemoryPcfBindingDao::Register(org::openapitools::server::model::PcfBinding binding) {
    const auto uuid = uuidGenerator->Generate();
    uuidToPcfPath[uuid] = binding;
    if (binding.getIpv4Addr().empty())
        macToUuid[binding.getMacAddr48()] = uuid;
    else if (binding.getMacAddr48().empty())
        ipv4ToUuid[binding.getIpv4Addr().data()] = uuid;
    else {
        macToUuid[binding.getMacAddr48()] = uuid;
        ipv4ToUuid[binding.getIpv4Addr().data()] = uuid;
    }
    return uuid;
};

std::optional<org::openapitools::server::model::PcfBinding> InMemoryPcfBindingDao::FindByIpv4(const std::string ipv4) {
    if (const auto it = ipv4ToUuid.find(ipv4); it != ipv4ToUuid.end()) {
        const auto uuid = it->second;
        if (const auto res = uuidToPcfPath.find(uuid); res != uuidToPcfPath.end())
            return res->second;
    }
    return std::nullopt;
}

std::optional<org::openapitools::server::model::PcfBinding> InMemoryPcfBindingDao::FindByMac(std::string mac) {
    if (const auto it = macToUuid.find(mac); it != macToUuid.end()) {
        const auto uuid = it->second;
        if (const auto res = uuidToPcfPath.find(uuid); res != uuidToPcfPath.end())
            return res->second;
    }
    return std::nullopt;
}
