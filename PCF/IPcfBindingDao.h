#pragma once
#include "../gen/model/PcfBinding.h"

class IPcfBindingDao {
public:
    virtual ~IPcfBindingDao() = default;
    virtual std::int64_t Register(org::openapitools::server::model::PcfBinding patch) = 0;
};