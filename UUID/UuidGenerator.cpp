#include <random>
#include "UuidGenerator.h"
#include <cstdint>

uint64_t UuidGenerator::Generate() {
    static std::random_device                     rd;
    static std::mt19937_64                        gen(rd());
    static std::uniform_int_distribution<int64_t> dis;
    return dis(gen);
}
