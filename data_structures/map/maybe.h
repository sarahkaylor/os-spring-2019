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

    // empty case
    Maybe()
        : is_present_(false),
          value_(nullptr)
    {}

    bool IsPresent() const {
        return is_present_;
    }

    const ValueType Value() const {
        return value_;
    }
};

}  // namespace map
}  // namespace data_structures

#endif //DOCUMENTS_MAP_H
