#include <gtest/gtest.h>
#include "vp/Exchange.h"

TEST(ExchangeTest, ToString) {
    ASSERT_EQ("Z", to_str(vp::Exchange::Z));
    ASSERT_EQ("I", to_str(vp::Exchange::I));
    ASSERT_EQ("M", to_str(vp::Exchange::M));
    ASSERT_EQ("U", to_str(vp::Exchange::U));
    ASSERT_EQ("L", to_str(vp::Exchange::L));
    ASSERT_EQ("W", to_str(vp::Exchange::W));
    ASSERT_EQ("X", to_str(vp::Exchange::X));
    ASSERT_EQ("B", to_str(vp::Exchange::B));
    ASSERT_EQ("D", to_str(vp::Exchange::D));
    ASSERT_EQ("J", to_str(vp::Exchange::J));
    ASSERT_EQ("P", to_str(vp::Exchange::P));
    ASSERT_EQ("Q", to_str(vp::Exchange::Q));
    ASSERT_EQ("S", to_str(vp::Exchange::S));
    ASSERT_EQ("V", to_str(vp::Exchange::V));
    ASSERT_EQ("A", to_str(vp::Exchange::A));
    ASSERT_EQ("E", to_str(vp::Exchange::E));
    ASSERT_EQ("N", to_str(vp::Exchange::N));
    ASSERT_EQ("T", to_str(vp::Exchange::T));
    ASSERT_EQ("Y", to_str(vp::Exchange::Y));
    ASSERT_EQ("C", to_str(vp::Exchange::C));
    ASSERT_EQ("H", to_str(vp::Exchange::H));
    ASSERT_EQ("K", to_str(vp::Exchange::K));
}

TEST(ExchangeTest, FromString) {
    ASSERT_EQ(vp::Exchange::Z, Exchange_from_str("Z"));
    ASSERT_EQ(vp::Exchange::I, Exchange_from_str("I"));
    ASSERT_EQ(vp::Exchange::M, Exchange_from_str("M"));
    ASSERT_EQ(vp::Exchange::U, Exchange_from_str("U"));
    ASSERT_EQ(vp::Exchange::L, Exchange_from_str("L"));
    ASSERT_EQ(vp::Exchange::W, Exchange_from_str("W"));
    ASSERT_EQ(vp::Exchange::X, Exchange_from_str("X"));
    ASSERT_EQ(vp::Exchange::B, Exchange_from_str("B"));
    ASSERT_EQ(vp::Exchange::D, Exchange_from_str("D"));
    ASSERT_EQ(vp::Exchange::J, Exchange_from_str("J"));
    ASSERT_EQ(vp::Exchange::P, Exchange_from_str("P"));
    ASSERT_EQ(vp::Exchange::Q, Exchange_from_str("Q"));
    ASSERT_EQ(vp::Exchange::S, Exchange_from_str("S"));
    ASSERT_EQ(vp::Exchange::V, Exchange_from_str("V"));
    ASSERT_EQ(vp::Exchange::A, Exchange_from_str("A"));
    ASSERT_EQ(vp::Exchange::E, Exchange_from_str("E"));
    ASSERT_EQ(vp::Exchange::N, Exchange_from_str("N"));
    ASSERT_EQ(vp::Exchange::T, Exchange_from_str("T"));
    ASSERT_EQ(vp::Exchange::Y, Exchange_from_str("Y"));
    ASSERT_EQ(vp::Exchange::C, Exchange_from_str("C"));
    ASSERT_EQ(vp::Exchange::H, Exchange_from_str("H"));
    ASSERT_EQ(vp::Exchange::K, Exchange_from_str("K"));
}

TEST(ExchangeTest, FromStringInvalid) {
    ASSERT_THROW(Exchange_from_str("invalid_exchange"), std::invalid_argument);
}

TEST(ExchangeTest, IsExchange) {
    ASSERT_TRUE(is_Exchange("Z"));
    ASSERT_TRUE(is_Exchange("I"));
    ASSERT_TRUE(is_Exchange("M"));
    ASSERT_TRUE(is_Exchange("U"));
    ASSERT_TRUE(is_Exchange("L"));
    ASSERT_TRUE(is_Exchange("W"));
    ASSERT_TRUE(is_Exchange("X"));
    ASSERT_TRUE(is_Exchange("B"));
    ASSERT_TRUE(is_Exchange("D"));
    ASSERT_TRUE(is_Exchange("J"));
    ASSERT_TRUE(is_Exchange("P"));
    ASSERT_TRUE(is_Exchange("Q"));
    ASSERT_TRUE(is_Exchange("S"));
    ASSERT_TRUE(is_Exchange("V"));
    ASSERT_TRUE(is_Exchange("A"));
    ASSERT_TRUE(is_Exchange("E"));
    ASSERT_TRUE(is_Exchange("N"));
    ASSERT_TRUE(is_Exchange("T"));
    ASSERT_TRUE(is_Exchange("Y"));
    ASSERT_TRUE(is_Exchange("C"));
    ASSERT_TRUE(is_Exchange("H"));
    ASSERT_TRUE(is_Exchange("K"));
    ASSERT_FALSE(is_Exchange("invalid_exchange"));
}
