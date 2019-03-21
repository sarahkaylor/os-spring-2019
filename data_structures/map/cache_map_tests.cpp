#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>
#include <semaphore.h>

#include "data_structures/map/cache_map.h"
#include "data_structures/map/string_hashes.h"
#include "gtest/gtest.h"

namespace data_structures {
namespace map{

constexpr int MAX_VALUE = 10000;
typedef CacheMap<std::string, std::string> StringCache;

namespace {

StringCache* create() {
    return new StringCache(CompareStrings, CalculateHash, 10000, std::string(""));
}

void addEvenValues(StringCache* cache) {
    for (auto i = 0; i < MAX_VALUE; i++) {
        if (i % 2 == 0) {
            std::string key = std::to_string(i);
            std::string value = cache->Get(
                    key,
                    [&]()-> std::string { return std::to_string(i*2); });
            if(std::to_string(i*2) != value) {
                return;
            }
        }
    }
}

void addOddValues(StringCache* cache) {
    for (auto i = 0; i < MAX_VALUE; i++) {
        if (i == 1 || i % 2 != 0) {
            std::string key = std::to_string(i);
            std::string value = cache->Get(
                    key,
                    [&]()-> std::string { return std::to_string(i*2); });
            if(std::to_string(i*2) != value) {
                return;
            }
        }
    }
}

void addForwards(StringCache* cache) {
    for (auto i = 0; i < MAX_VALUE; i++) {
        std::string key = std::to_string(i);
        std::string value = cache->Get(
                key,
                [&]()-> std::string { return std::to_string(i*2); });
        if(std::to_string(i*2) != value) {
            return;
        }
    }
}

void addBackwards(StringCache* cache) {
    for (auto i = MAX_VALUE-1; i >= 0; i--) {
        std::string key = std::to_string(i);
        std::string value = cache->Get(
                key,
                [&]()-> std::string { return std::to_string(i*2); });
        if(std::to_string(i*2) != value) {
            return;
        }
    }
}

} // namespace

TEST(CacheMapTests, testInitialSize) {
    auto map = std::unique_ptr<StringCache>(create());

    EXPECT_EQ(0, map->size());
}

TEST(CacheMapTests, testGetReturnsEmpty) {
    auto map = std::unique_ptr<StringCache>(create());

    auto result = map->Get("foo");

    EXPECT_FALSE(result.IsPresent());
}

TEST(CacheMapTests, testMultiThreadedAdd) {
    auto map = std::unique_ptr<StringCache>(create());

    std::thread t1(addEvenValues, map.get());
    std::thread t2(addOddValues, map.get());

    t1.join();
    t2.join();

    EXPECT_EQ(MAX_VALUE, map->size());

    for (auto i = 0; i < MAX_VALUE; i++) {
        if (i % 2 == 0) {
            std::string key = std::to_string(i);
            std::string value = map->Get(
                    key,
                    [&]()-> std::string { return std::string("-1"); });
            EXPECT_EQ(std::to_string(i*2), value);
            if(std::to_string(i*2) != value) {
                break;
            }
        }
    }

    EXPECT_EQ(MAX_VALUE, map->size());
}

TEST(CacheMapTests, testMultiThreadedAdd2) {
    auto map = std::unique_ptr<StringCache>(create());

    std::thread t1(addForwards, map.get());
    std::thread t2(addBackwards, map.get());

    t1.join();
    t2.join();

    EXPECT_EQ(MAX_VALUE, map->size());

    for (auto i = 0; i < MAX_VALUE; i++) {
        if (i % 2 == 0) {
            std::string key = std::to_string(i);
            std::string value = map->Get(
                    key,
                    [&]()-> std::string { return std::string("-1"); });
            EXPECT_EQ(std::to_string(i*2), value);
            if(std::to_string(i*2) != value) {
                break;
            }
        }
    }

    EXPECT_EQ(MAX_VALUE, map->size());
}

namespace {

std::atomic_int32_t counter_;
sem_t slow_event_;
sem_t fast_event_;
sem_t slow_event_done_;
sem_t fast_event_done_;

void FastGet(StringCache* cache) {
    auto key = std::to_string(counter_.load(std::memory_order_seq_cst));
    std::string value = cache->Get(
            key,
            [&]() -> std::string {
                sem_wait(&fast_event_);
                auto value_to_add = counter_.load(std::memory_order_seq_cst);
                return std::to_string(value_to_add);
            }
            );
    auto counter_value = counter_.load(std::memory_order_seq_cst);
    EXPECT_EQ(
            std::to_string(counter_value),
            value);
    sem_post(&fast_event_done_);
}

void SlowGet(StringCache* cache) {
    auto key = std::to_string(counter_.load(std::memory_order_seq_cst) + 1);
    std::string value = cache->Get(
            key,
            [&]() -> std::string {
                sem_wait(&slow_event_);
                auto value_to_add = ++counter_;
                return std::to_string(value_to_add);
            }
    );
    auto counter_value = counter_.load(std::memory_order_seq_cst);
    EXPECT_EQ(
            std::to_string(counter_value),
            value);
    sem_post(&slow_event_done_);
}

} // namespace

TEST(CacheMapTests, testTwoGetsCanHappenSimultaneously) {
    counter_ = 0;
    sem_init(&fast_event_, 0, 0);
    sem_init(&slow_event_, 0, 0);
    sem_init(&fast_event_done_, 0, 0);
    sem_init(&slow_event_done_, 0, 0);

    for(auto i = 0; i < 1000; i += 2) {
        auto map = std::unique_ptr<StringCache>(create());
        std::thread fast(FastGet, map.get());
        std::thread slow(SlowGet, map.get());

        sem_post(&fast_event_);
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
        sem_post(&slow_event_);

        sem_wait(&fast_event_done_);

        auto key = std::to_string(i);
        auto value = map->Get(key);

        EXPECT_EQ(key, value.Value());

        slow.join();
        fast.join();

        sem_wait(&slow_event_done_);

        if(key != value.Value()) {
            return;
        }

        key = std::to_string(i+1);
        value = map->Get(key);

        EXPECT_EQ(key, value.Value());
        if(key != value.Value()) {
            return;
        }

        ++counter_;
    }
}

}
}