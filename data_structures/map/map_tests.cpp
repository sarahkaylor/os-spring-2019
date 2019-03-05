#include <string>

#include "data_structures/map/map_impl.h"
#include "data_structures/map/string_hashes.h"
#include "gtest/gtest.h"

namespace data_structures {
namespace map {

typedef MapImpl<std::string, std::string> StringMap;

namespace {

StringMap create() {
    return StringMap(CompareStrings, CalculateHash, 10000, std::string(""));
}

StringMap createWithBadHash() {
    return StringMap(CompareStrings, CalculateBadHash, 10000, std::string(""));
}

} // namespace

TEST(MapTests, testInitialSize) {
    StringMap map = create();

    EXPECT_EQ(0, map.Size());
}

TEST(MapTests, testPutThenGet) {
    StringMap map = create();

    map.Put("a", "abc");

    auto result = map.Get("a");

    EXPECT_TRUE(result.IsPresent());
    if(result.IsPresent()) {
        EXPECT_EQ("abc", result.Value());
    }
}

TEST(MapTests, testPutThenGet_BadHash) {
    StringMap map = createWithBadHash();

    map.Put("a", "abc");

    auto result = map.Get("a");

    EXPECT_TRUE(result.IsPresent());
    if(result.IsPresent()) {
        EXPECT_EQ("abc", result.Value());
    }
}

TEST(MapTests, testPutTwiceOverwritesAndIncreasesSizeOnlyOnce) {
    StringMap map = create();

    map.Put("a", "abc");

    EXPECT_EQ(1, map.Size());

    auto result1 = map.Get("a");
    EXPECT_TRUE(result1.IsPresent());
    if(result1.IsPresent()) {
        EXPECT_EQ("abc", result1.Value());
    }

    map.Put("a", "def");

    EXPECT_EQ(1, map.Size());

    auto result2 = map.Get("a");
    EXPECT_TRUE(result2.IsPresent());
    if(result2.IsPresent()) {
        EXPECT_EQ("def", result2.Value());
    }
}

TEST(MapTests, testPutTwiceOverwritesAndIncreasesSizeOnlyOnce_BadHash) {
    StringMap map = createWithBadHash();

    map.Put("a", "abc");

    EXPECT_EQ(1, map.Size());

    auto result1 = map.Get("a");
    EXPECT_TRUE(result1.IsPresent());
    if(result1.IsPresent()) {
        EXPECT_EQ("abc", result1.Value());
    }

    map.Put("a", "def");

    EXPECT_EQ(1, map.Size());

    auto result2 = map.Get("a");
    EXPECT_TRUE(result2.IsPresent());
    if(result2.IsPresent()) {
        EXPECT_EQ("def", result2.Value());
    }
}

TEST(MapTests, testRemove) {
    StringMap map = create();

    EXPECT_EQ(0, map.Size());

    map.Put("a", "abc");

    EXPECT_EQ(1, map.Size());
    EXPECT_TRUE(map.Remove("a"));
    EXPECT_EQ(0, map.Size());
    EXPECT_FALSE(map.Remove("a"));
}

TEST(MapTests, testRemove_BadHash) {
    StringMap map = createWithBadHash();

    EXPECT_EQ(0, map.Size());

    map.Put("a", "abc");

    EXPECT_EQ(1, map.Size());
    EXPECT_TRUE(map.Remove("a"));
    EXPECT_EQ(0, map.Size());
    EXPECT_FALSE(map.Remove("a"));
}

}  // namespace map
}  // namespace data_structures