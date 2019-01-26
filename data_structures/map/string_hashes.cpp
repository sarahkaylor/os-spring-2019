#include "data_structures/map/string_hashes.h"

namespace data_structures {
namespace map{

bool CompareStrings(const std::string& str1, const std::string& str2) {
    return str1 == str2;
}

constexpr uint32_t FNV_PRIME = 16777619U;
constexpr uint32_t FNV_OFFSET = 2166136261U;

uint32_t CalculateHash(const std::string& str) {
    // a FNV-1a hash
    uint32_t hash = FNV_OFFSET;
    for (char i : str) {
        auto value = (uint32_t) i;
        hash = hash ^ value;
        hash = hash * FNV_PRIME;
    }
    return hash;
}

uint32_t CalculateBadHash(const std::string& str) {
    return 0U;
}

}
}