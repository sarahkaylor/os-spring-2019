#ifndef DOCUMENTS_CACHE_MAP_H
#define DOCUMENTS_CACHE_MAP_H

#include <functional>
#include "data_structures/map/maybe.h"

namespace data_structures {
namespace map {

template<typename KeyType, typename ValueType>
class CacheMap {
public:
    typedef std::function<bool(const KeyType&, const KeyType&)> KeyComparerFn;
    typedef std::function<uint32_t(const KeyType&)> HashCalculator;
    typedef std::function<ValueType()> ValueFactory;

private:
    const KeyComparerFn key_comparer_;
    const HashCalculator hash_calculator_;
    const uint32_t capacity_;
    const ValueType empty_value_;

public:
    CacheMap(const KeyComparerFn key_comparer,
             const HashCalculator hash_calculator,
             const uint32_t capacity, const ValueType empty_value)
            : key_comparer_(key_comparer), hash_calculator_(hash_calculator),
              capacity_(capacity), empty_value_(empty_value) {}

    ValueType Get(const KeyType& key, ValueFactory create_value) {
        return ValueType();
    }

    Maybe<ValueType> Get(const KeyType& key) const {
        return EmptyMaybe(empty_value_);
    }

    int size() const {
        return 0;
    }

};

}  // namespace map
}  // namespace data_structures

#endif //DOCUMENTS_CACHE_MAP_H
