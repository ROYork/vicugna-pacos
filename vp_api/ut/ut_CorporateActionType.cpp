#include <gtest/gtest.h>
#include "vp/CorporateActionType.h"

TEST(CorporateActionTypeTest, ToString) {
    ASSERT_EQ("dividend", to_str(vp::CorporateActionType::dividend));
    ASSERT_EQ("merger", to_str(vp::CorporateActionType::merger));
    ASSERT_EQ("spinoff", to_str(vp::CorporateActionType::spinoff));
    ASSERT_EQ("split", to_str(vp::CorporateActionType::split));
}

TEST(CorporateActionTypeTest, FromString) {
    ASSERT_EQ(vp::CorporateActionType::dividend, CorporateActionType_from_str("dividend"));
    ASSERT_EQ(vp::CorporateActionType::merger, CorporateActionType_from_str("merger"));
    ASSERT_EQ(vp::CorporateActionType::spinoff, CorporateActionType_from_str("spinoff"));
    ASSERT_EQ(vp::CorporateActionType::split, CorporateActionType_from_str("split"));
}

TEST(CorporateActionTypeTest, FromStringInvalid) {
    ASSERT_THROW(CorporateActionType_from_str("invalid_type"), std::invalid_argument);
}

TEST(CorporateActionTypeTest, IsCorporateActionType) {
    ASSERT_TRUE(is_CorporateActionType("dividend"));
    ASSERT_TRUE(is_CorporateActionType("merger"));
    ASSERT_TRUE(is_CorporateActionType("spinoff"));
    ASSERT_TRUE(is_CorporateActionType("split"));
    ASSERT_FALSE(is_CorporateActionType("invalid_type"));
}
