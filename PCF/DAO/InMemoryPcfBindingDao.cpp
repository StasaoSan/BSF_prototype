#include <string>
#include "InMemoryPcfBindingDao.h"
#include "../../gen/model/PcfBinding.h"

std::int64_t InMemoryPcfBindingDao::Register(org::openapitools::server::model::PcfBinding binding) {
    const auto uuid = uuidGenerator->Generate();
    uuidToPcfPath[uuid] = binding;

    ipv4ToUuid[binding.getIpv4Addr().data()] = uuid;
    return uuid;
};

std::optional<org::openapitools::server::model::PcfBinding> InMemoryPcfBindingDao::FindByIpv4(const std::string ipv4) {
    if (const auto it = ipv4ToUuid.find(ipv4); it != ipv4ToUuid.end()) {
        const auto uuid = it->second;
        if (const auto res = uuidToPcfPath.find(uuid); res != uuidToPcfPath.end()) {
            return res->second;
        }
    }
    return std::nullopt;
}
