#include <gtest/gtest.h>
#include "vp/AssetClass.h"

TEST(AssetClassTest, ToString) {
    ASSERT_EQ("us_equity", to_str(vp::AssetClass::us_equity));
    ASSERT_EQ("us_option", to_str(vp::AssetClass::us_option));
    ASSERT_EQ("crypto", to_str(vp::AssetClass::crypto));
}

TEST(AssetClassTest, FromString) {
    ASSERT_EQ(vp::AssetClass::us_equity, AssetClass_from_str("us_equity"));
    ASSERT_EQ(vp::AssetClass::us_option, AssetClass_from_str("us_option"));
    ASSERT_EQ(vp::AssetClass::crypto, AssetClass_from_str("crypto"));
}

TEST(AssetClassTest, FromStringInvalid) {
    ASSERT_THROW(AssetClass_from_str("invalid_asset_class"), std::invalid_argument);
}

TEST(AssetClassTest, IsAssetClass) {
    ASSERT_TRUE(is_AssetClass("us_equity"));
    ASSERT_TRUE(is_AssetClass("us_option"));
    ASSERT_TRUE(is_AssetClass("crypto"));
    ASSERT_FALSE(is_AssetClass("invalid_asset_class"));
}
