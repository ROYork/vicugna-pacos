#include <gtest/gtest.h>
#include "vp/CorporateActionSubType.h"

TEST(CorporateActionSubTypeTest, ToString) {
    ASSERT_EQ("cash", to_str(vp::CorporateActionSubType::cash));
    ASSERT_EQ("stock", to_str(vp::CorporateActionSubType::stock));
    ASSERT_EQ("merger_update", to_str(vp::CorporateActionSubType::merger_update));
    ASSERT_EQ("merger_completion", to_str(vp::CorporateActionSubType::merger_completion));
    ASSERT_EQ("spinoff", to_str(vp::CorporateActionSubType::spinoff));
    ASSERT_EQ("stock_split", to_str(vp::CorporateActionSubType::stock_split));
    ASSERT_EQ("unit_split", to_str(vp::CorporateActionSubType::unit_split));
    ASSERT_EQ("reverse_split", to_str(vp::CorporateActionSubType::reverse_split));
    ASSERT_EQ("recapitalization", to_str(vp::CorporateActionSubType::recapitalization));
}

TEST(CorporateActionSubTypeTest, FromString) {
    ASSERT_EQ(vp::CorporateActionSubType::cash, CorporateActionSubType_from_str("cash"));
    ASSERT_EQ(vp::CorporateActionSubType::stock, CorporateActionSubType_from_str("stock"));
    ASSERT_EQ(vp::CorporateActionSubType::merger_update, CorporateActionSubType_from_str("merger_update"));
    ASSERT_EQ(vp::CorporateActionSubType::merger_completion, CorporateActionSubType_from_str("merger_completion"));
    ASSERT_EQ(vp::CorporateActionSubType::spinoff, CorporateActionSubType_from_str("spinoff"));
    ASSERT_EQ(vp::CorporateActionSubType::stock_split, CorporateActionSubType_from_str("stock_split"));
    ASSERT_EQ(vp::CorporateActionSubType::unit_split, CorporateActionSubType_from_str("unit_split"));
    ASSERT_EQ(vp::CorporateActionSubType::reverse_split, CorporateActionSubType_from_str("reverse_split"));
    ASSERT_EQ(vp::CorporateActionSubType::recapitalization, CorporateActionSubType_from_str("recapitalization"));
}

TEST(CorporateActionSubTypeTest, FromStringInvalid) {
    ASSERT_THROW(CorporateActionSubType_from_str("invalid_subtype"), std::invalid_argument);
}

TEST(CorporateActionSubTypeTest, IsCorporateActionSubType) {
    ASSERT_TRUE(is_CorporateActionSubType("cash"));
    ASSERT_TRUE(is_CorporateActionSubType("stock"));
    ASSERT_TRUE(is_CorporateActionSubType("merger_update"));
    ASSERT_TRUE(is_CorporateActionSubType("merger_completion"));
    ASSERT_TRUE(is_CorporateActionSubType("spinoff"));
    ASSERT_TRUE(is_CorporateActionSubType("stock_split"));
    ASSERT_TRUE(is_CorporateActionSubType("unit_split"));
    ASSERT_TRUE(is_CorporateActionSubType("reverse_split"));
    ASSERT_TRUE(is_CorporateActionSubType("recapitalization"));
    ASSERT_FALSE(is_CorporateActionSubType("invalid_subtype"));
}
