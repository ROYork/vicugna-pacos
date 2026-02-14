#include <gtest/gtest.h>
#include "vp/OrderSide.h"

TEST(OrderSideTest, ToString) {
    ASSERT_EQ("buy", to_str(vp::OrderSide::buy));
    ASSERT_EQ("sell", to_str(vp::OrderSide::sell));
}

TEST(OrderSideTest, FromString) {
    ASSERT_EQ(vp::OrderSide::buy, OrderSide_from_str("buy"));
    ASSERT_EQ(vp::OrderSide::sell, OrderSide_from_str("sell"));
}

TEST(OrderSideTest, FromStringInvalid) {
    ASSERT_THROW(OrderSide_from_str("invalid_side"), std::invalid_argument);
}

TEST(OrderSideTest, IsOrderSide) {
    ASSERT_TRUE(is_OrderSide("buy"));
    ASSERT_TRUE(is_OrderSide("sell"));
    ASSERT_FALSE(is_OrderSide("invalid_side"));
}
