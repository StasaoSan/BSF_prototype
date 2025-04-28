#pragma once
#include <cstdint>
#include "../../gen/model/PcfBinding.h"

class IPcfBindingService {
public:
    virtual ~IPcfBindingService() = default;

    virtual int64_t Register(org::openapitools::server::model::PcfBinding binding) = 0;
};
