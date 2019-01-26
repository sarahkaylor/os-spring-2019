#ifndef DOCUMENTS_MAP_IMPL_H
#define DOCUMENTS_MAP_IMPL_H

#include <string>
#include <memory>
#include <functional>
#include "data_structures/map/maybe.h"

namespace data_structures {
namespace map {

template<typename KeyType, typename ValueType>
class MapImpl {
public:
    typedef std::function<bool(const KeyType&, const KeyType&)> KeyComparerFn;
    typedef std::function<uint32_t(const KeyType&)> HashCalculator;
private:
    const KeyComparerFn key_comparer_;
    const HashCalculator hash_calculator_;
    const uint32_t capacity_;
public:

    MapImpl(const KeyComparerFn key_comparer,
            const HashCalculator hash_calculator, const uint32_t capacity)
        : key_comparer_(key_comparer), hash_calculator_(hash_calculator),
          capacity_(capacity)
    {}

    int Size() const {
        return -1;
    }

    void Put(const KeyType& key, const ValueType& value) {
    }

    bool Remove(const KeyType& key) {
        return false;
    }

    Maybe<ValueType> Get(const KeyType& key) const {
        return Maybe<ValueType>();
    }
private:

    uint32_t GetIndex(const KeyType& key) const {
        uint32_t hash = hash_calculator_(key);
        uint32_t index = hash % capacity_;
        return index;
    }
};

}  // namespace map
}  // namespace data_structures

#endif //DOCUMENTS_MAP_IMPL_H
