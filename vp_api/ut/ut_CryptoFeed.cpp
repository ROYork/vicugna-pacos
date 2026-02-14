#include <gtest/gtest.h>
#include "vp/CryptoFeed.h"

TEST(CryptoFeedTest, ToString) {
    ASSERT_EQ("us", to_str(vp::CryptoFeed::us));
}

TEST(CryptoFeedTest, FromString) {
    ASSERT_EQ(vp::CryptoFeed::us, CryptoFeed_from_str("us"));
}

TEST(CryptoFeedTest, FromStringInvalid) {
    ASSERT_THROW(CryptoFeed_from_str("invalid_feed"), std::invalid_argument);
}

TEST(CryptoFeedTest, IsCryptoFeed) {
    ASSERT_TRUE(is_CryptoFeed("us"));
    ASSERT_FALSE(is_CryptoFeed("invalid_feed"));
}
