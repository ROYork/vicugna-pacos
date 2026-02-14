#include <gtest/gtest.h>
#include "vp/TimeFrameUnit.h"
#include <format>

TEST(TimeFrameUnitTest, ToString) {
    ASSERT_EQ("Min", to_str(vp::TimeFrameUnit::Minute));
    ASSERT_EQ("Hour", to_str(vp::TimeFrameUnit::Hour));
    ASSERT_EQ("Day", to_str(vp::TimeFrameUnit::Day));
    ASSERT_EQ("Week", to_str(vp::TimeFrameUnit::Week));
    ASSERT_EQ("Month", to_str(vp::TimeFrameUnit::Month));
}

//Verify to_json() returns quoted version of to_string()
TEST(TimeFrameUnitTest, ToStringJson) {

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::TimeFrameUnit::Minute)).c_str(),
                to_json(vp::TimeFrameUnit::Minute).c_str());

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::TimeFrameUnit::Hour)).c_str(),
               to_json(vp::TimeFrameUnit::Hour).c_str());

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::TimeFrameUnit::Day)).c_str(),
               to_json(vp::TimeFrameUnit::Day).c_str());

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::TimeFrameUnit::Week)).c_str(),
               to_json(vp::TimeFrameUnit::Week).c_str());

  ASSERT_STREQ(std::format("\"{}\"", to_str(vp::TimeFrameUnit::Month)).c_str(),
               to_json(vp::TimeFrameUnit::Month).c_str());


}

TEST(TimeFrameUnitTest, FromString) {
    ASSERT_EQ(vp::TimeFrameUnit::Minute, TimeFrameUnit_from_str("Min"));
    ASSERT_EQ(vp::TimeFrameUnit::Hour, TimeFrameUnit_from_str("Hour"));
    ASSERT_EQ(vp::TimeFrameUnit::Day, TimeFrameUnit_from_str("Day"));
    ASSERT_EQ(vp::TimeFrameUnit::Week, TimeFrameUnit_from_str("Week"));
    ASSERT_EQ(vp::TimeFrameUnit::Month, TimeFrameUnit_from_str("Month"));
}

TEST(TimeFrameUnitTest, FromStringInvalid) {
    ASSERT_THROW(TimeFrameUnit_from_str("invalid_unit"), std::invalid_argument);
}

TEST(TimeFrameUnitTest, IsTimeFrameUnit) {
    ASSERT_TRUE(is_TimeFrameUnit("Min"));
    ASSERT_TRUE(is_TimeFrameUnit("Hour"));
    ASSERT_TRUE(is_TimeFrameUnit("Day"));
    ASSERT_TRUE(is_TimeFrameUnit("Week"));
    ASSERT_TRUE(is_TimeFrameUnit("Month"));
    ASSERT_FALSE(is_TimeFrameUnit("invalid_unit"));
}
