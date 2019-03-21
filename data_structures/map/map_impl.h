#ifndef DOCUMENTS_MAP_IMPL_H
#define DOCUMENTS_MAP_IMPL_H

#include <string>
#include <memory>
#include <functional>
#include <utility>
#include <vector>
#include "data_structures/map/maybe.h"

namespace data_structures {
namespace map {

template<typename KeyType, typename ValueType>
class MapImpl {
public:
    typedef std::function<bool(const KeyType&, const KeyType&)> KeyComparerFn;
    typedef std::function<uint32_t(const KeyType&)> HashCalculator;
private:

    typedef std::pair<KeyType, ValueType> MapEntry;
    typedef std::vector<MapEntry> MapList;

    const KeyComparerFn key_comparer_;
    const HashCalculator hash_calculator_;
    const uint32_t capacity_;
    const ValueType empty_value_;
    uint32_t size_;
    std::unique_ptr<MapList[]> storage_;
public:

    MapImpl(const KeyComparerFn key_comparer,
            const HashCalculator hash_calculator, const uint32_t capacity,
            const ValueType empty_value)
        : key_comparer_(key_comparer), hash_calculator_(hash_calculator),
          capacity_(capacity), empty_value_(empty_value),
          size_(0), storage_(new MapList[capacity])
    {}

    int Size() const {
        return (int)size_;
    }

    void Put(const KeyType& key, const ValueType& value) {
        auto index = GetIndex(key);
        MapList& list = storage_.get()[index];
        MapEntry new_entry = {key,value};
        for(auto it = list.begin();
            it != list.end(); it++) {
            MapEntry& entry = *it;
            if(key_comparer_(entry.first, key)) {
                list.erase(it);
                list.emplace_back(new_entry);
                return;
            }
        }
        list.emplace_back(new_entry);
        ++size_;
    }

    bool Remove(const KeyType& key) {
        auto index = GetIndex(key);
        MapList& list = storage_.get()[index];
        for(auto it = list.begin();
            it != list.end(); ++it) {
            MapEntry& entry = *it;
            if(key_comparer_(entry.first, key)) {
                list.erase(it);
                --size_;
                return true;
            }
        }
        return false;
    }

    Maybe<ValueType> Get(const KeyType& key) const {
        auto index = GetIndex(key);
        MapList& list = storage_.get()[index];
        for(auto it = list.begin();
            it != list.end(); ++it) {
            MapEntry& entry = *it;
            if(key_comparer_(entry.first, key)) {
                return Maybe<ValueType>(entry.second);
            }
        }
        return EmptyMaybe(empty_value_);
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
