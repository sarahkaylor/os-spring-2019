#include <memory>
#include <string>
#include <thread>
#include <atomic>
#include <chrono>

#include "data_structures/map/cache_map.h"
#include "data_structures/map/string_hashes.h"
#include "gtest/gtest.h"

namespace data_structures {
namespace map{

constexpr int MAX_VALUE = 1000000;
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
        if (i % 3 == 0) {
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
    for (auto i = MAX_VALUE; i >= 0; i--) {
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

void FastGet(StringCache* cache) {
    std::string value = cache->Get(
            std::to_string(counter_.load(std::memory_order_seq_cst)),
            [&]() -> std::string {
                std::this_thread::sleep_for(std::chrono::microseconds(500));
                return std::to_string(
                    counter_.load(std::memory_order_seq_cst)
                    );
            }
            );
    EXPECT_EQ(
            std::to_string(counter_.load(std::memory_order_seq_cst)),
            value);
}

void SlowGet(StringCache* cache) {
    std::string value = cache->Get(
            std::to_string(counter_.load(std::memory_order_seq_cst)),
            [&]() -> std::string {
                std::this_thread::sleep_for(std::chrono::seconds(2));
                counter_++;
                return std::to_string(
                    counter_.load(std::memory_order_seq_cst));
            }
    );
    EXPECT_EQ(
            std::to_string(counter_.load(std::memory_order_seq_cst)),
            value);
}

} // namespace

TEST(CacheMapTests, testTwoGetsCanHappenSimultaneously) {
    counter_ = 0;

    for(auto i = 0; i < 1000; i += 2) {
        auto map = std::unique_ptr<StringCache>(create());
        std::thread slow(SlowGet, map.get());
        std::thread fast(FastGet, map.get());

        std::this_thread::sleep_for(std::chrono::seconds(1));

        EXPECT_EQ(
                std::to_string(i),
                map->Get(std::to_string(i)).Value());

        slow.join();
        fast.join();

        EXPECT_EQ(
                std::to_string(i),
                map->Get(std::to_string(i)).Value());
        if(std::to_string(i) != map->Get(std::to_string(i)).Value()) {
            return;
        }
    }
}

}
}