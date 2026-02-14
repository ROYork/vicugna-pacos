#include <gtest/gtest.h>
#include "vp/CorporateActionDateType.h"

TEST(CorporateActionDateTypeTest, ToString) {
    ASSERT_EQ("declaration_date", to_str(vp::CorporateActionDateType::declaration_date));
    ASSERT_EQ("ex_date", to_str(vp::CorporateActionDateType::ex_date));
    ASSERT_EQ("record_date", to_str(vp::CorporateActionDateType::record_date));
    ASSERT_EQ("payable_date", to_str(vp::CorporateActionDateType::payable_date));
}

TEST(CorporateActionDateTypeTest, FromString) {
    ASSERT_EQ(vp::CorporateActionDateType::declaration_date, CorporateActionDateType_from_str("declaration_date"));
    ASSERT_EQ(vp::CorporateActionDateType::ex_date, CorporateActionDateType_from_str("ex_date"));
    ASSERT_EQ(vp::CorporateActionDateType::record_date, CorporateActionDateType_from_str("record_date"));
    ASSERT_EQ(vp::CorporateActionDateType::payable_date, CorporateActionDateType_from_str("payable_date"));
}

TEST(CorporateActionDateTypeTest, FromStringInvalid) {
    ASSERT_THROW(CorporateActionDateType_from_str("invalid_date_type"), std::invalid_argument);
}

TEST(CorporateActionDateTypeTest, IsCorporateActionDateType) {
    ASSERT_TRUE(is_CorporateActionDateType("declaration_date"));
    ASSERT_TRUE(is_CorporateActionDateType("ex_date"));
    ASSERT_TRUE(is_CorporateActionDateType("record_date"));
    ASSERT_TRUE(is_CorporateActionDateType("payable_date"));
    ASSERT_FALSE(is_CorporateActionDateType("invalid_date_type"));
}
