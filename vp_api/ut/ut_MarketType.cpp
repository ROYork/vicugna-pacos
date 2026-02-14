#include <gtest/gtest.h>
#include "vp/MarketType.h"

TEST(MarketTypeTest, ToString) {
    ASSERT_EQ("stocks", to_str(vp::MarketType::stocks));
    ASSERT_EQ("crypto", to_str(vp::MarketType::crypto));
}

TEST(MarketTypeTest, FromString) {
    ASSERT_EQ(vp::MarketType::stocks, MarketType_from_str("stocks"));
    ASSERT_EQ(vp::MarketType::crypto, MarketType_from_str("crypto"));
}

TEST(MarketTypeTest, FromStringInvalid) {
    ASSERT_THROW(MarketType_from_str("invalid_type"), std::invalid_argument);
}

TEST(MarketTypeTest, IsMarketType) {
    ASSERT_TRUE(is_MarketType("stocks"));
    ASSERT_TRUE(is_MarketType("crypto"));
    ASSERT_FALSE(is_MarketType("invalid_type"));
}
