#include <gtest/gtest.h>
#include "vp/Adjustment.h"

TEST(AdjustmentTest, ToString) {
    ASSERT_EQ("raw", to_str(vp::Adjustment::raw));
    ASSERT_EQ("split", to_str(vp::Adjustment::split));
    ASSERT_EQ("dividend", to_str(vp::Adjustment::dividend));
    ASSERT_EQ("all", to_str(vp::Adjustment::all));
}

TEST(AdjustmentTest, ToJson) {
  ASSERT_EQ("\"raw\"", to_json(vp::Adjustment::raw));
  ASSERT_EQ("\"split\"", to_json(vp::Adjustment::split));
  ASSERT_EQ("\"dividend\"", to_json(vp::Adjustment::dividend));
  ASSERT_EQ("\"all\"", to_json(vp::Adjustment::all));
}

TEST(AdjustmentTest, FromString) {
    ASSERT_EQ(vp::Adjustment::raw, Adjustment_from_str("raw"));
    ASSERT_EQ(vp::Adjustment::split, Adjustment_from_str("split"));
    ASSERT_EQ(vp::Adjustment::dividend, Adjustment_from_str("dividend"));
    ASSERT_EQ(vp::Adjustment::all, Adjustment_from_str("all"));
}

TEST(AdjustmentTest, FromStringInvalid) {
    ASSERT_THROW(Adjustment_from_str("invalid_adjustment"), std::invalid_argument);
}

TEST(AdjustmentTest, IsAdjustment) {
    ASSERT_TRUE(is_Adjustment("raw"));
    ASSERT_TRUE(is_Adjustment("split"));
    ASSERT_TRUE(is_Adjustment("dividend"));
    ASSERT_TRUE(is_Adjustment("all"));
    ASSERT_FALSE(is_Adjustment("invalid_adjustment"));
}
