#include "gtest/gtest.h"
#include <BloomFilter.h>

namespace bloom_filter {
namespace bloom_filter_test {

class BloomFilterUnitTest : public ::testing::Test {};

    TEST_F(BloomFilterUnitTest, smallBloomFilter) {
        std::vector<std::string> keys = {
                "f",
                "far",
                "fast",
                "s",
                "top",
                "toy",
                "trie",
        };
        auto filter = BloomFilter(keys, 200);

        for (const auto& key : keys) {
            ASSERT_TRUE(filter.lookupKey(key));
        }

        ASSERT_FALSE(filter.lookupKey("stop"));
        ASSERT_FALSE(filter.lookupKey("false_positive"));
    }

    TEST_F(BloomFilterUnitTest, memoryUsage) {
        std::vector<std::string> keys = {
                "f",
                "far",
                "fast",
                "s",
                "top",
                "toy",
                "trie",
        };
        auto tiny_filter = BloomFilter(keys, 32);
        auto small_filter = BloomFilter(keys, 256);
        auto medium_filter = BloomFilter(keys, 1024);
        auto large_filter = BloomFilter(keys, 4096);

        auto size_tiny_filter = tiny_filter.getMemoryUsage();
        auto size_small_filter = small_filter.getMemoryUsage();
        auto size_medium_filter = medium_filter.getMemoryUsage();
        auto size_large_filter = large_filter.getMemoryUsage();

        ASSERT_GT(size_small_filter, size_tiny_filter);
        ASSERT_GT(size_large_filter, size_medium_filter);
        ASSERT_GT(size_medium_filter, size_small_filter);

        ASSERT_GT(tiny_filter.getFPR(), small_filter.getFPR());
        ASSERT_GT(small_filter.getFPR(), medium_filter.getFPR());
        ASSERT_GT(medium_filter.getFPR(), large_filter.getFPR());
    }
}
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}