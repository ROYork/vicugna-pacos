#include <gtest/gtest.h>
#include "vp/OrderType.h"

TEST(OrderTypeTest, ToString) {
    ASSERT_EQ("market", to_str(vp::OrderType::market));
    ASSERT_EQ("limit", to_str(vp::OrderType::limit));
    ASSERT_EQ("stop", to_str(vp::OrderType::stop));
    ASSERT_EQ("stop_limit", to_str(vp::OrderType::stop_limit));
    ASSERT_EQ("trailing_stop", to_str(vp::OrderType::trailing_stop));
}

TEST(OrderTypeTest, FromString) {
    ASSERT_EQ(vp::OrderType::market, OrderType_from_str("market"));
    ASSERT_EQ(vp::OrderType::limit, OrderType_from_str("limit"));
    ASSERT_EQ(vp::OrderType::stop, OrderType_from_str("stop"));
    ASSERT_EQ(vp::OrderType::stop_limit, OrderType_from_str("stop_limit"));
    ASSERT_EQ(vp::OrderType::trailing_stop, OrderType_from_str("trailing_stop"));
}

TEST(OrderTypeTest, FromStringInvalid) {
    ASSERT_THROW(OrderType_from_str("invalid_type"), std::invalid_argument);
}

TEST(OrderTypeTest, IsOrderType) {
    ASSERT_TRUE(is_OrderType("market"));
    ASSERT_TRUE(is_OrderType("limit"));
    ASSERT_TRUE(is_OrderType("stop"));
    ASSERT_TRUE(is_OrderType("stop_limit"));
    ASSERT_TRUE(is_OrderType("trailing_stop"));
    ASSERT_FALSE(is_OrderType("invalid_type"));
}
