#include <gtest/gtest.h>
#include "vp/PDTCheck.h"

TEST(PDTCheckTest, ToString) {
    ASSERT_EQ("both", to_str(vp::PDTCheck::both));
    ASSERT_EQ("entry", to_str(vp::PDTCheck::entry));
    ASSERT_EQ("exit", to_str(vp::PDTCheck::exit));
}

TEST(PDTCheckTest, FromString) {
    ASSERT_EQ(vp::PDTCheck::both, PDTCheck_from_str("both"));
    ASSERT_EQ(vp::PDTCheck::entry, PDTCheck_from_str("entry"));
    ASSERT_EQ(vp::PDTCheck::exit, PDTCheck_from_str("exit"));
}

TEST(PDTCheckTest, FromStringInvalid) {
    ASSERT_THROW(PDTCheck_from_str("invalid_check"), std::invalid_argument);
}

TEST(PDTCheckTest, IsPDTCheck) {
    ASSERT_TRUE(is_PDTCheck("both"));
    ASSERT_TRUE(is_PDTCheck("entry"));
    ASSERT_TRUE(is_PDTCheck("exit"));
    ASSERT_FALSE(is_PDTCheck("invalid_check"));
}
