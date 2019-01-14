#ifndef DATA_STRUCTURES_QUEUE_H_
#define DATA_STRUCTURES_QUEUE_H_

#include <memory>
#include <assert.h>

namespace data_structures {

template<typename ValueType>
class Queue {
private:
	std::unique_ptr<ValueType[]> array_;
	int front_;
	int rear_;
	int capacity_;
	int size_;
public:
	Queue() {
		front_ = -1;
		rear_ = -1;
		capacity_ = 2;
		size_ = 0;
		array_ = std::unique_ptr<ValueType[]>(new ValueType[2]);
	}

	int size() { return size_; }

	void addLast(const ValueType& value) {
		ensureCapacity(++size_);
		if(front_ == -1 && rear_ == -1) {
			front_ = rear_ = 0;
		} else {
			rear_ = (rear_+1) % capacity_;
		}
		array_.get()[rear_] = std::move(value);
	}

	ValueType removeFirst() {
		assert(--size_ >= 0);
		ValueType value = std::move(array_.get()[front_]);
		if(rear_ == front_) {
			rear_ = front_ = -1;
		} else {
			front_ = (front_+1) % capacity_;
		}
		return value;
	}

private:
	void ensureCapacity(int size) {
	    assert(capacity_ > 0);
	    assert(size > 0);
		if(capacity_ < size) {
			capacity_ = (capacity_ == 0)
				? 2
				: capacity_ * 2;
			std::unique_ptr<ValueType[]> newArray = std::unique_ptr<ValueType[]>(new ValueType[capacity_]);
			for(int i = front_; i <= rear_; i++) {
				assert(i >= 0);
				newArray.get()[i] = std::move(array_.get()[i]);
			}
			array_ = std::move(newArray);
		}
	}
};

} // namespace data_structures

#endif // DATA_STRUCTURES_QUEUE_H_
