#include <gtest/gtest.h>
#include "vp/DTBPCheck.h"

TEST(DTBPCheckTest, ToString) {
    ASSERT_EQ("both", to_str(vp::DTBPCheck::both));
    ASSERT_EQ("entry", to_str(vp::DTBPCheck::entry));
    ASSERT_EQ("exit", to_str(vp::DTBPCheck::exit));
}

TEST(DTBPCheckTest, ToJson) {
  ASSERT_EQ("\"both\"",  to_json(vp::DTBPCheck::both));
  ASSERT_EQ("\"entry\"", to_json(vp::DTBPCheck::entry));
  ASSERT_EQ("\"exit\"",  to_json(vp::DTBPCheck::exit));
}

TEST(DTBPCheckTest, ToJsonNotEqualString) {
  ASSERT_NE(to_str(vp::DTBPCheck::both), to_json(vp::DTBPCheck::both));
  ASSERT_NE(to_str(vp::DTBPCheck::entry), to_json(vp::DTBPCheck::entry));
  ASSERT_NE(to_str(vp::DTBPCheck::exit),  to_json(vp::DTBPCheck::exit));
}

TEST(DTBPCheckTest, FromString) {
    ASSERT_EQ(vp::DTBPCheck::both, DTBPCheck_from_str("both"));
    ASSERT_EQ(vp::DTBPCheck::entry, DTBPCheck_from_str("entry"));
    ASSERT_EQ(vp::DTBPCheck::exit, DTBPCheck_from_str("exit"));
}

TEST(DTBPCheckTest, FromStringInvalid) {
    ASSERT_THROW(DTBPCheck_from_str("invalid_check"), std::invalid_argument);
}

TEST(DTBPCheckTest, IsDTBPCheck) {
    ASSERT_TRUE(is_DTBPCheck("both"));
    ASSERT_TRUE(is_DTBPCheck("entry"));
    ASSERT_TRUE(is_DTBPCheck("exit"));
    ASSERT_FALSE(is_DTBPCheck("invalid_check"));
}
