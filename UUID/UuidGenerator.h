#pragma once
#include "IUuidGenerator.h"
#include <cstdint>
class UuidGenerator : public IUuidGenerator {
public:
    uint64_t Generate() override;
};