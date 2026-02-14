#include <gtest/gtest.h>
#include "vp/TradeEvent.h"

TEST(TradeEventTest, ToString) {
    ASSERT_EQ("fill", to_str(vp::TradeEvent::fill));
    ASSERT_EQ("canceled", to_str(vp::TradeEvent::canceled));
    ASSERT_EQ("pending_new", to_str(vp::TradeEvent::pending_new));
    ASSERT_EQ("new", to_str(vp::TradeEvent::new_));
    ASSERT_EQ("partial_fill", to_str(vp::TradeEvent::partial_fill));
}

TEST(TradeEventTest, FromString) {
    ASSERT_EQ(vp::TradeEvent::fill, TradeEvent_from_str("fill"));
    ASSERT_EQ(vp::TradeEvent::canceled, TradeEvent_from_str("canceled"));
    ASSERT_EQ(vp::TradeEvent::pending_new, TradeEvent_from_str("pending_new"));
    ASSERT_EQ(vp::TradeEvent::new_, TradeEvent_from_str("new"));
    ASSERT_EQ(vp::TradeEvent::partial_fill, TradeEvent_from_str("partial_fill"));
}

TEST(TradeEventTest, FromStringInvalid) {
    ASSERT_THROW(TradeEvent_from_str("invalid_event"), std::invalid_argument);
}

TEST(TradeEventTest, IsTradeEvent) {
    ASSERT_TRUE(is_TradeEvent("fill"));
    ASSERT_TRUE(is_TradeEvent("canceled"));
    ASSERT_TRUE(is_TradeEvent("pending_new"));
    ASSERT_TRUE(is_TradeEvent("new"));
    ASSERT_TRUE(is_TradeEvent("partial_fill"));
    ASSERT_FALSE(is_TradeEvent("invalid_event"));
}
