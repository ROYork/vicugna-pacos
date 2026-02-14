#include <gtest/gtest.h>
#include "vp/AssetStatus.h"

TEST(AssetStatusTest, ToString) {
    ASSERT_EQ("active", to_str(vp::AssetStatus::active));
    ASSERT_EQ("inactive", to_str(vp::AssetStatus::inactive));
}

TEST(AssetStatusTest, FromString) {
    ASSERT_EQ(vp::AssetStatus::active, AssetStatus_from_str("active"));
    ASSERT_EQ(vp::AssetStatus::inactive, AssetStatus_from_str("inactive"));
}

TEST(AssetStatusTest, FromStringInvalid) {
    ASSERT_THROW(AssetStatus_from_str("invalid_status"), std::invalid_argument);
}

TEST(AssetStatusTest, IsAssetStatus) {
    ASSERT_TRUE(is_AssetStatus("active"));
    ASSERT_TRUE(is_AssetStatus("inactive"));
    ASSERT_FALSE(is_AssetStatus("invalid_status"));
}
