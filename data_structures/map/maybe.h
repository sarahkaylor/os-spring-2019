#ifndef DOCUMENTS_MAP_H
#define DOCUMENTS_MAP_H

namespace data_structures {
namespace map {

template<typename ValueType>
class Maybe {
private:
    const bool is_present_;
    const ValueType value_;
public:

    // we have an actual value
    explicit Maybe(const ValueType& value)
        : is_present_(true),
          value_(value)
    {}

    bool IsPresent() const {
        return is_present_;
    }

    const ValueType Value() const {
        return value_;
    }

    // empty case
    Maybe(ValueType value, bool is_present)
            : is_present_(is_present),
              value_(value)
    {}
};

template <typename ValueType>
Maybe<ValueType> EmptyMaybe(ValueType empty_value) {
    return Maybe<ValueType>(empty_value, false);
}

}  // namespace map
}  // namespace data_structures

#endif //DOCUMENTS_MAP_H
