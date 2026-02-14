#include <gtest/gtest.h>
#include "vp/MostActivesBy.h"

TEST(MostActivesByTest, ToString) {
    ASSERT_EQ("volume", to_str(vp::MostActivesBy::volume));
    ASSERT_EQ("trades", to_str(vp::MostActivesBy::trades));
}

TEST(MostActivesByTest, FromString) {
    ASSERT_EQ(vp::MostActivesBy::volume, MostActivesBy_from_str("volume"));
    ASSERT_EQ(vp::MostActivesBy::trades, MostActivesBy_from_str("trades"));
}

TEST(MostActivesByTest, FromStringInvalid) {
    ASSERT_THROW(MostActivesBy_from_str("invalid_type"), std::invalid_argument);
}

TEST(MostActivesByTest, IsMostActivesBy) {
    ASSERT_TRUE(is_MostActivesBy("volume"));
    ASSERT_TRUE(is_MostActivesBy("trades"));
    ASSERT_FALSE(is_MostActivesBy("invalid_type"));
}
