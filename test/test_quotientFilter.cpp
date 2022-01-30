#include "gtest/gtest.h"
#include <QuotientFilter.h>

namespace quotient_filter {
    namespace quotient_filter_test {

    class QuotientFilterUnitTest : public ::testing::Test {};

    TEST_F(QuotientFilterUnitTest, smallQuotientFilter) {
            std::vector<std::string> keys = {
                    "f",
                    "far",
                    "fast",
                    "s",
                    "top",
                    "toy",
                    "trash",
                    "trie",
                    "trr"
            };
            auto filter = QuotientFilter(keys, 3, 4);

            for (const auto& key : keys) {
                ASSERT_TRUE(filter.lookupKey(key));
            }

            ASSERT_FALSE(filter.lookupKey("stop"));
            ASSERT_FALSE(filter.lookupKey("false_positive"));
    }

    TEST_F(QuotientFilterUnitTest, memoryUsage) {
        std::vector<std::string> keys = {
                "f",
                "far",
                "fast",
                "s",
                "top",
                "toy",
                "trie",
        };
        auto tiny_filter = QuotientFilter(keys, 3, 4);
        auto small_filter = QuotientFilter(keys, 4, 5);
        auto medium_filter = QuotientFilter(keys, 5, 6);
        auto large_filter = QuotientFilter(keys, 6, 7);

        auto size_tiny_filter = tiny_filter.getMemoryUsage();
        auto size_small_filter = small_filter.getMemoryUsage();
        auto size_medium_filter = medium_filter.getMemoryUsage();
        auto size_large_filter = large_filter.getMemoryUsage();

        ASSERT_GT(size_small_filter, size_tiny_filter);
        ASSERT_GT(size_large_filter, size_medium_filter);
        ASSERT_GT(size_medium_filter, size_small_filter);
    }
    }
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}