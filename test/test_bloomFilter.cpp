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
}
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}