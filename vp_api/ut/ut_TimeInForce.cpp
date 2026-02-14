#include <gtest/gtest.h>
#include "vp/TimeInForce.h"

TEST(TimeInForceTest, ToString) {
    ASSERT_EQ("day", to_str(vp::TimeInForce::day));
    ASSERT_EQ("gtc", to_str(vp::TimeInForce::gtc));
    ASSERT_EQ("opg", to_str(vp::TimeInForce::opg));
    ASSERT_EQ("cls", to_str(vp::TimeInForce::cls));
    ASSERT_EQ("ioc", to_str(vp::TimeInForce::ioc));
    ASSERT_EQ("fok", to_str(vp::TimeInForce::fok));
}

TEST(TimeInForceTest, FromString) {
    ASSERT_EQ(vp::TimeInForce::day, TimeInForce_from_str("day"));
    ASSERT_EQ(vp::TimeInForce::gtc, TimeInForce_from_str("gtc"));
    ASSERT_EQ(vp::TimeInForce::opg, TimeInForce_from_str("opg"));
    ASSERT_EQ(vp::TimeInForce::cls, TimeInForce_from_str("cls"));
    ASSERT_EQ(vp::TimeInForce::ioc, TimeInForce_from_str("ioc"));
    ASSERT_EQ(vp::TimeInForce::fok, TimeInForce_from_str("fok"));
}

TEST(TimeInForceTest, FromStringInvalid) {
    ASSERT_THROW(TimeInForce_from_str("invalid_tif"), std::invalid_argument);
}

TEST(TimeInForceTest, IsTimeInForce) {
    ASSERT_TRUE(is_TimeInForce("day"));
    ASSERT_TRUE(is_TimeInForce("gtc"));
    ASSERT_TRUE(is_TimeInForce("opg"));
    ASSERT_TRUE(is_TimeInForce("cls"));
    ASSERT_TRUE(is_TimeInForce("ioc"));
    ASSERT_TRUE(is_TimeInForce("fok"));
    ASSERT_FALSE(is_TimeInForce("invalid_tif"));
}
