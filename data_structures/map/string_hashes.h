#ifndef DOCUMENTS_STRING_HASHES_H
#define DOCUMENTS_STRING_HASHES_H

#include <string>

namespace data_structures {
namespace map {

bool CompareStrings(const std::string& str1, const std::string& str2);
uint32_t CalculateHash(const std::string& str);
uint32_t CalculateBadHash(const std::string& str);

}
}
#endif //DOCUMENTS_STRING_HASHES_H
