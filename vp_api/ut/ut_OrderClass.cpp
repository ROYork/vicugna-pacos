#include <gtest/gtest.h>
#include "vp/OrderClass.h"

TEST(OrderClassTest, ToString) {
    ASSERT_EQ("simple", to_str(vp::OrderClass::simple));
    ASSERT_EQ("mleg", to_str(vp::OrderClass::mleg));
    ASSERT_EQ("bracket", to_str(vp::OrderClass::bracket));
    ASSERT_EQ("oco", to_str(vp::OrderClass::oco));
    ASSERT_EQ("oto", to_str(vp::OrderClass::oto));
}

TEST(OrderClassTest, FromString) {
    ASSERT_EQ(vp::OrderClass::simple, OrderClass_from_str("simple"));
    ASSERT_EQ(vp::OrderClass::mleg, OrderClass_from_str("mleg"));
    ASSERT_EQ(vp::OrderClass::bracket, OrderClass_from_str("bracket"));
    ASSERT_EQ(vp::OrderClass::oco, OrderClass_from_str("oco"));
    ASSERT_EQ(vp::OrderClass::oto, OrderClass_from_str("oto"));
}

TEST(OrderClassTest, FromStringInvalid) {
    ASSERT_THROW(OrderClass_from_str("invalid_class"), std::invalid_argument);
}

TEST(OrderClassTest, IsOrderClass) {
    ASSERT_TRUE(is_OrderClass("simple"));
    ASSERT_TRUE(is_OrderClass("mleg"));
    ASSERT_TRUE(is_OrderClass("bracket"));
    ASSERT_TRUE(is_OrderClass("oco"));
    ASSERT_TRUE(is_OrderClass("oto"));
    ASSERT_FALSE(is_OrderClass("invalid_class"));
}
