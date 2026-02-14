#include <gtest/gtest.h>
#include "vp/TimeFrame.h"

using namespace vp;
using namespace vp::timeframe;

// =============================================================================
// Tests for Constants
// =============================================================================

TEST(TimeFrameTest, Constants) {
    ASSERT_EQ("1Min", MINUTE_1);
    ASSERT_EQ("1Hour", HOUR_1);
    ASSERT_EQ("1Day", DAY_1);
    ASSERT_EQ("1Week", WEEK_1);
    ASSERT_EQ("1Month", MONTH_1);
}

// =============================================================================
// Tests for make() Function
// =============================================================================

TEST(TimeFrameTest, MakeFunction_ValidCases) {
    ASSERT_EQ("1Min", make(1, TimeFrameUnit::Minute));
    ASSERT_EQ("5Min", make(5, TimeFrameUnit::Minute));
    ASSERT_EQ("59Min", make(59, TimeFrameUnit::Minute));

    ASSERT_EQ("1Hour", make(1, TimeFrameUnit::Hour));
    ASSERT_EQ("5Hour", make(5, TimeFrameUnit::Hour));
    ASSERT_EQ("23Hour", make(23, TimeFrameUnit::Hour));

    ASSERT_EQ("1Day", make(1, TimeFrameUnit::Day));
    ASSERT_EQ("1Week", make(1, TimeFrameUnit::Week));

    ASSERT_EQ("1Month", make(1, TimeFrameUnit::Month));
    ASSERT_EQ("2Month", make(2, TimeFrameUnit::Month));
    ASSERT_EQ("3Month", make(3, TimeFrameUnit::Month));
    ASSERT_EQ("6Month", make(6, TimeFrameUnit::Month));
    ASSERT_EQ("12Month", make(12, TimeFrameUnit::Month));
}

TEST(TimeFrameTest, MakeFunction_InvalidAmount) {
    ASSERT_THROW(make(0, TimeFrameUnit::Minute), std::invalid_argument);
    ASSERT_THROW(make(-1, TimeFrameUnit::Minute), std::invalid_argument);
}

TEST(TimeFrameTest, MakeFunction_InvalidMinuteAmount) {
    ASSERT_THROW(make(60, TimeFrameUnit::Minute), std::invalid_argument);
    ASSERT_THROW(make(100, TimeFrameUnit::Minute), std::invalid_argument);
}

TEST(TimeFrameTest, MakeFunction_InvalidHourAmount) {
    ASSERT_THROW(make(24, TimeFrameUnit::Hour), std::invalid_argument);
    ASSERT_THROW(make(25, TimeFrameUnit::Hour), std::invalid_argument);
}

TEST(TimeFrameTest, MakeFunction_InvalidDayWeekAmount) {
    ASSERT_THROW(make(2, TimeFrameUnit::Day), std::invalid_argument);
    ASSERT_THROW(make(0, TimeFrameUnit::Week), std::invalid_argument);
    ASSERT_THROW(make(2, TimeFrameUnit::Week), std::invalid_argument);
}

TEST(TimeFrameTest, MakeFunction_InvalidMonthAmount) {
    ASSERT_THROW(make(4, TimeFrameUnit::Month), std::invalid_argument);
    ASSERT_THROW(make(5, TimeFrameUnit::Month), std::invalid_argument);
    ASSERT_THROW(make(13, TimeFrameUnit::Month), std::invalid_argument);
}

// =============================================================================
// Tests for Validation Function
// =============================================================================

TEST(TimeFrameTest, Validate_ValidCases) {
    ASSERT_NO_THROW(validate(1, TimeFrameUnit::Minute));
    ASSERT_NO_THROW(validate(59, TimeFrameUnit::Minute));
    ASSERT_NO_THROW(validate(1, TimeFrameUnit::Hour));
    ASSERT_NO_THROW(validate(23, TimeFrameUnit::Hour));
    ASSERT_NO_THROW(validate(1, TimeFrameUnit::Day));
    ASSERT_NO_THROW(validate(1, TimeFrameUnit::Week));
    ASSERT_NO_THROW(validate(1, TimeFrameUnit::Month));
    ASSERT_NO_THROW(validate(12, TimeFrameUnit::Month));
}

TEST(TimeFrameTest, Validate_InvalidCases) {
    ASSERT_THROW(validate(0, TimeFrameUnit::Minute), std::invalid_argument);
    ASSERT_THROW(validate(-1, TimeFrameUnit::Minute), std::invalid_argument);
    ASSERT_THROW(validate(60, TimeFrameUnit::Minute), std::invalid_argument);
    ASSERT_THROW(validate(24, TimeFrameUnit::Hour), std::invalid_argument);
}

// =============================================================================
// Tests for Helper Functions
// =============================================================================

TEST(TimeFrameTest, HelperFunction_Minutes) {
    ASSERT_EQ("1Min", minutes());      // Default
    ASSERT_EQ("1Min", minutes(1));
    ASSERT_EQ("5Min", minutes(5));
    ASSERT_EQ("15Min", minutes(15));
    ASSERT_EQ("59Min", minutes(59));

    ASSERT_THROW(minutes(0), std::invalid_argument);
    ASSERT_THROW(minutes(60), std::invalid_argument);
}

TEST(TimeFrameTest, HelperFunction_Hours) {
    ASSERT_EQ("1Hour", hours());       // Default
    ASSERT_EQ("1Hour", hours(1));
    ASSERT_EQ("2Hour", hours(2));
    ASSERT_EQ("23Hour", hours(23));

    ASSERT_THROW(hours(0), std::invalid_argument);
    ASSERT_THROW(hours(24), std::invalid_argument);
}

TEST(TimeFrameTest, HelperFunction_Day) {
    ASSERT_EQ("1Day", day());
}

TEST(TimeFrameTest, HelperFunction_Week) {
    ASSERT_EQ("1Week", week());
}

TEST(TimeFrameTest, HelperFunction_Months) {
    ASSERT_EQ("1Month", months());     // Default
    ASSERT_EQ("1Month", months(1));
    ASSERT_EQ("2Month", months(2));
    ASSERT_EQ("3Month", months(3));
    ASSERT_EQ("6Month", months(6));
    ASSERT_EQ("12Month", months(12));

    ASSERT_THROW(months(4), std::invalid_argument);
    ASSERT_THROW(months(5), std::invalid_argument);
    ASSERT_THROW(months(13), std::invalid_argument);
}
