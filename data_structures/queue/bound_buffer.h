#ifndef DOCUMENTS_BOUND_BUFFER_H
#define DOCUMENTS_BOUND_BUFFER_H

namespace data_structures {
template<typename ValueType>
class BoundBuffer {

private:
    const int max_size_;

public:

    explicit BoundBuffer(int max_size) : max_size_(max_size) {}

    int size() { return 0; }

    void addLast(const ValueType& value) {

    }

    ValueType removeFirst() {
        return ValueType();
    }
};

} // namespace data_structures

#endif //DOCUMENTS_BOUND_BUFFER_H
