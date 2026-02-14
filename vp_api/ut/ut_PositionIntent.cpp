#include <gtest/gtest.h>
#include "vp/PositionIntent.h"

TEST(PositionIntentTest, ToString) {
    ASSERT_EQ("buy_to_open", to_str(vp::PositionIntent::buy_to_open));
    ASSERT_EQ("buy_to_close", to_str(vp::PositionIntent::buy_to_close));
    ASSERT_EQ("sell_to_open", to_str(vp::PositionIntent::sell_to_open));
    ASSERT_EQ("sell_to_close", to_str(vp::PositionIntent::sell_to_close));
}

TEST(PositionIntentTest, FromString) {
    ASSERT_EQ(vp::PositionIntent::buy_to_open, PositionIntent_from_str("buy_to_open"));
    ASSERT_EQ(vp::PositionIntent::buy_to_close, PositionIntent_from_str("buy_to_close"));
    ASSERT_EQ(vp::PositionIntent::sell_to_open, PositionIntent_from_str("sell_to_open"));
    ASSERT_EQ(vp::PositionIntent::sell_to_close, PositionIntent_from_str("sell_to_close"));
}

TEST(PositionIntentTest, FromStringInvalid) {
    ASSERT_THROW(PositionIntent_from_str("invalid_intent"), std::invalid_argument);
}

TEST(PositionIntentTest, IsPositionIntent) {
    ASSERT_TRUE(is_PositionIntent("buy_to_open"));
    ASSERT_TRUE(is_PositionIntent("buy_to_close"));
    ASSERT_TRUE(is_PositionIntent("sell_to_open"));
    ASSERT_TRUE(is_PositionIntent("sell_to_close"));
    ASSERT_FALSE(is_PositionIntent("invalid_intent"));
}
