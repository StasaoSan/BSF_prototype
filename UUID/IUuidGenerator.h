#pragma once
#include <string>
#include <cstdint>

class IUuidGenerator {
public:
    virtual ~IUuidGenerator() = default;
    virtual uint64_t Generate() = 0;
};