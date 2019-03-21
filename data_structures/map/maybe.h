#ifndef DOCUMENTS_MAP_H
#define DOCUMENTS_MAP_H

namespace data_structures {
namespace map {

template<typename ValueType>
class Maybe {
private:
    bool is_present_;
    ValueType value_;
public:

    // we have an actual value
    explicit Maybe(const ValueType& value)
        : is_present_(true),
          value_(value)
    {}

    Maybe(const Maybe<ValueType>& value)
        : is_present_(value.IsPresent()),
        value_(value.Value())
    {
    }

    Maybe<ValueType>& operator=(const Maybe<ValueType>& value) noexcept {
        is_present_ = value.is_present_;
        value_ = value.Value();
        return *this;
    }

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
