#include <memory>
#include <thread>
#include <atomic>
#include <iostream>
#include "data_structures/queue/bound_buffer.h"
#include "gtest/gtest.h"

namespace data_structures {
namespace map {

constexpr int MAX_QUEUE_SIZE = 5;
constexpr int MAX_TO_ADD = 10000;
typedef BoundBuffer<int32_t> IntBuffer;

namespace {

std::atomic_int32_t max_add_size_;
std::atomic_int32_t max_consume_size_;

IntBuffer* create() {
    return new IntBuffer(MAX_QUEUE_SIZE);
}

void addManyValues(IntBuffer* queue) {
    for(int i = 0; i < MAX_TO_ADD; i++) {
        queue->addLast(i);
        auto size = queue->size();
        if(max_add_size_ < size) {
            max_add_size_ = size;
        }
    }
}

void consumeManyValues(IntBuffer* queue, std::vector<int>* values_removed) {
    for(int i = 0; i < MAX_TO_ADD; i++) {
        auto value = queue->removeFirst();
        auto size = queue->size();
        if(max_consume_size_ < size) {
            max_consume_size_ = size;
        }
        values_removed->emplace_back(value);
    }
}
}

TEST(BoundBufferTests, testProduceAndConsume) {
    max_add_size_ = 0;
    max_consume_size_ = 0;

    auto queue = std::unique_ptr<IntBuffer>(create());

    EXPECT_EQ(0, queue->size());

    std::vector<int> values_removed;

    std::thread producer(addManyValues, queue.get());
    std::thread consumer(consumeManyValues, queue.get(), &values_removed);

    producer.join();
    consumer.join();

    EXPECT_EQ(0, queue->size());
    EXPECT_LT(max_add_size_, MAX_QUEUE_SIZE);
    EXPECT_LT(max_consume_size_, MAX_QUEUE_SIZE);

    EXPECT_EQ(MAX_TO_ADD, (int)values_removed.size());
    for(int i = 0; i < MAX_TO_ADD; i++) {
        EXPECT_EQ(i, values_removed[i]);
    }
}

}
}
