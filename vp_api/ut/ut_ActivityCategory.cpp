#include <gtest/gtest.h>
#include "vp/ActivityCategory.h"

TEST(ActivityCategoryTest, ToString) {
    ASSERT_EQ("trade_activity", to_str(vp::ActivityCategory::trade_activity));
    ASSERT_EQ("non_trade_activity", to_str(vp::ActivityCategory::non_trade_activity));
}

TEST(ActivityCategoryTest, ToStringCstr) {
  ASSERT_STREQ("trade_activity", to_str(vp::ActivityCategory::trade_activity).c_str());
  ASSERT_STREQ("non_trade_activity", to_str(vp::ActivityCategory::non_trade_activity).c_str());
}

//Verify to_json() returns quoted version of to_string()
TEST(ActivityCategoryTest, ToJson) {
  ASSERT_STREQ("\"trade_activity\"",
               to_json(vp::ActivityCategory::trade_activity).c_str());

  ASSERT_STREQ("\"non_trade_activity\"",
               to_json(vp::ActivityCategory::non_trade_activity).c_str());

  ASSERT_STREQ("\"trade_activity\"",
               to_json(vp::ActivityCategory::trade_activity).c_str());

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::ActivityCategory::non_trade_activity)).c_str(),
               to_json(vp::ActivityCategory::non_trade_activity).c_str());

  ASSERT_STREQ( std::format("\"{}\"", to_str(vp::ActivityCategory::trade_activity)).c_str(),
                to_json(vp::ActivityCategory::trade_activity).c_str());
}

TEST(ActivityCategoryTest, FromString) {
    ASSERT_EQ(vp::ActivityCategory::trade_activity, ActivityCategory_from_str("trade_activity"));
    ASSERT_EQ(vp::ActivityCategory::non_trade_activity, ActivityCategory_from_str("non_trade_activity"));
}

TEST(ActivityCategoryTest, FromStringInvalid) {
    ASSERT_THROW(ActivityCategory_from_str("invalid_category"), std::invalid_argument);
}

TEST(ActivityCategoryTest, IsActivityCategory) {
    ASSERT_TRUE(is_ActivityCategory("trade_activity"));
    ASSERT_TRUE(is_ActivityCategory("non_trade_activity"));
    ASSERT_FALSE(is_ActivityCategory("invalid_category"));
}
