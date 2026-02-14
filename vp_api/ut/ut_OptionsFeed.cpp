#include <gtest/gtest.h>
#include "vp/OptionsFeed.h"

TEST(OptionsFeedTest, ToString) {
    ASSERT_EQ("opra", to_str(vp::OptionsFeed::opra));
    ASSERT_EQ("indicative", to_str(vp::OptionsFeed::indicative));
}

TEST(OptionsFeedTest, FromString) {
    ASSERT_EQ(vp::OptionsFeed::opra, OptionsFeed_from_str("opra"));
    ASSERT_EQ(vp::OptionsFeed::indicative, OptionsFeed_from_str("indicative"));
}

TEST(OptionsFeedTest, FromStringInvalid) {
    ASSERT_THROW(OptionsFeed_from_str("invalid_feed"), std::invalid_argument);
}

TEST(OptionsFeedTest, IsOptionsFeed) {
    ASSERT_TRUE(is_OptionsFeed("opra"));
    ASSERT_TRUE(is_OptionsFeed("indicative"));
    ASSERT_FALSE(is_OptionsFeed("invalid_feed"));
}
