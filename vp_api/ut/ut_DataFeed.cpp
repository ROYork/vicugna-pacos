#include <gtest/gtest.h>
#include "vp/DataFeed.h"

TEST(DataFeedTest, ToString) {
    ASSERT_EQ("iex", to_str(vp::DataFeed::iex));
    ASSERT_EQ("sip", to_str(vp::DataFeed::sip));
    ASSERT_EQ("delayed_sip", to_str(vp::DataFeed::delayed_sip));
    ASSERT_EQ("otc", to_str(vp::DataFeed::otc));
    ASSERT_EQ("boats", to_str(vp::DataFeed::boats));
    ASSERT_EQ("overnight", to_str(vp::DataFeed::overnight));
}

TEST(DataFeedTest, ToJson) {
  ASSERT_EQ("\"iex\"", to_json(vp::DataFeed::iex));
  ASSERT_EQ("\"sip\"", to_json(vp::DataFeed::sip));
  ASSERT_EQ("\"delayed_sip\"", to_json(vp::DataFeed::delayed_sip));
  ASSERT_EQ("\"otc\"", to_json(vp::DataFeed::otc));
  ASSERT_EQ("\"boats\"", to_json(vp::DataFeed::boats));
  ASSERT_EQ("\"overnight\"", to_json(vp::DataFeed::overnight));
}

TEST(DataFeedTest, FromString) {
    ASSERT_EQ(vp::DataFeed::iex, DataFeed_from_str("iex"));
    ASSERT_EQ(vp::DataFeed::sip, DataFeed_from_str("sip"));
    ASSERT_EQ(vp::DataFeed::delayed_sip, DataFeed_from_str("delayed_sip"));
    ASSERT_EQ(vp::DataFeed::otc, DataFeed_from_str("otc"));
    ASSERT_EQ(vp::DataFeed::boats, DataFeed_from_str("boats"));
    ASSERT_EQ(vp::DataFeed::overnight, DataFeed_from_str("overnight"));
}

TEST(DataFeedTest, FromStringInvalid) {
    ASSERT_THROW(DataFeed_from_str("invalid_feed"), std::invalid_argument);
}

TEST(DataFeedTest, IsDataFeed) {
    ASSERT_TRUE(is_DataFeed("iex"));
    ASSERT_TRUE(is_DataFeed("sip"));
    ASSERT_TRUE(is_DataFeed("delayed_sip"));
    ASSERT_TRUE(is_DataFeed("otc"));
    ASSERT_TRUE(is_DataFeed("boats"));
    ASSERT_TRUE(is_DataFeed("overnight"));
    ASSERT_FALSE(is_DataFeed("invalid_feed"));
}
