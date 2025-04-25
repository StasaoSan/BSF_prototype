#pragma once
#include <string>

class IUuidGenerator {
public:
    virtual ~IUuidGenerator() = default;
    virtual int64_t Generate() = 0;
};