#include <gtest/gtest.h>
#include "vp/PositionSide.h"

TEST(PositionSideTest, ToString) {
    ASSERT_EQ("short", to_str(vp::PositionSide::short_));
    ASSERT_EQ("long", to_str(vp::PositionSide::long_));
}

TEST(PositionSideTest, FromString) {
    ASSERT_EQ(vp::PositionSide::short_, PositionSide_from_str("short"));
    ASSERT_EQ(vp::PositionSide::long_, PositionSide_from_str("long"));
}

TEST(PositionSideTest, FromStringInvalid) {
    ASSERT_THROW(PositionSide_from_str("invalid_side"), std::invalid_argument);
}

TEST(PositionSideTest, IsPositionSide) {
    ASSERT_TRUE(is_PositionSide("short"));
    ASSERT_TRUE(is_PositionSide("long"));
    ASSERT_FALSE(is_PositionSide("invalid_side"));
}
