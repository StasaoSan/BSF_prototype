#pragma once
#include "IUuidGenerator.h"

class UuidGenerator : public IUuidGenerator {
public:
    int64_t Generate() override;
};