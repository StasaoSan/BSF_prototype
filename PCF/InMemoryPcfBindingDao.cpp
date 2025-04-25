#include <string>
#include "InMemoryPcfBindingDao.h"

#include "../gen/model/PcfBinding.h"

std::int64_t InMemoryPcfBindingDao::Register(org::openapitools::server::model::PcfBinding binding) {
    const auto uuid = uuidGenerator->Generate();
    uuidToPcfPath[uuid] = binding;

    ipv4ToUuid[binding.getIpv4Addr().data()] = uuid;
    return uuid;
};
