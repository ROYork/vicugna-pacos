#include <gtest/gtest.h>
#include "vp/CorporateActionsType.h"

TEST(CorporateActionsTypeTest, ToString) {
    ASSERT_EQ("reverse_split", to_str(vp::CorporateActionsType::reverse_split));
    ASSERT_EQ("forward_split", to_str(vp::CorporateActionsType::forward_split));
    ASSERT_EQ("unit_split", to_str(vp::CorporateActionsType::unit_split));
    ASSERT_EQ("cash_dividend", to_str(vp::CorporateActionsType::cash_dividend));
    ASSERT_EQ("stock_dividend", to_str(vp::CorporateActionsType::stock_dividend));
    ASSERT_EQ("spin_off", to_str(vp::CorporateActionsType::spin_off));
    ASSERT_EQ("cash_merger", to_str(vp::CorporateActionsType::cash_merger));
    ASSERT_EQ("stock_merger", to_str(vp::CorporateActionsType::stock_merger));
    ASSERT_EQ("stock_and_cash_merger", to_str(vp::CorporateActionsType::stock_and_cash_merger));
    ASSERT_EQ("redemption", to_str(vp::CorporateActionsType::redemption));
    ASSERT_EQ("name_change", to_str(vp::CorporateActionsType::name_change));
    ASSERT_EQ("worthless_removal", to_str(vp::CorporateActionsType::worthless_removal));
    ASSERT_EQ("rights_distribution", to_str(vp::CorporateActionsType::rights_distribution));
}

TEST(CorporateActionsTypeTest, FromString) {
    ASSERT_EQ(vp::CorporateActionsType::reverse_split, CorporateActionsType_from_str("reverse_split"));
    ASSERT_EQ(vp::CorporateActionsType::forward_split, CorporateActionsType_from_str("forward_split"));
    ASSERT_EQ(vp::CorporateActionsType::unit_split, CorporateActionsType_from_str("unit_split"));
    ASSERT_EQ(vp::CorporateActionsType::cash_dividend, CorporateActionsType_from_str("cash_dividend"));
    ASSERT_EQ(vp::CorporateActionsType::stock_dividend, CorporateActionsType_from_str("stock_dividend"));
    ASSERT_EQ(vp::CorporateActionsType::spin_off, CorporateActionsType_from_str("spin_off"));
    ASSERT_EQ(vp::CorporateActionsType::cash_merger, CorporateActionsType_from_str("cash_merger"));
    ASSERT_EQ(vp::CorporateActionsType::stock_merger, CorporateActionsType_from_str("stock_merger"));
    ASSERT_EQ(vp::CorporateActionsType::stock_and_cash_merger, CorporateActionsType_from_str("stock_and_cash_merger"));
    ASSERT_EQ(vp::CorporateActionsType::redemption, CorporateActionsType_from_str("redemption"));
    ASSERT_EQ(vp::CorporateActionsType::name_change, CorporateActionsType_from_str("name_change"));
    ASSERT_EQ(vp::CorporateActionsType::worthless_removal, CorporateActionsType_from_str("worthless_removal"));
    ASSERT_EQ(vp::CorporateActionsType::rights_distribution, CorporateActionsType_from_str("rights_distribution"));
}

TEST(CorporateActionsTypeTest, FromStringInvalid) {
    ASSERT_THROW(CorporateActionsType_from_str("invalid_type"), std::invalid_argument);
}

TEST(CorporateActionsTypeTest, IsCorporateActionsType) {
    ASSERT_TRUE(is_CorporateActionsType("reverse_split"));
    ASSERT_TRUE(is_CorporateActionsType("forward_split"));
    ASSERT_TRUE(is_CorporateActionsType("unit_split"));
    ASSERT_TRUE(is_CorporateActionsType("cash_dividend"));
    ASSERT_TRUE(is_CorporateActionsType("stock_dividend"));
    ASSERT_TRUE(is_CorporateActionsType("spin_off"));
    ASSERT_TRUE(is_CorporateActionsType("cash_merger"));
    ASSERT_TRUE(is_CorporateActionsType("stock_merger"));
    ASSERT_TRUE(is_CorporateActionsType("stock_and_cash_merger"));
    ASSERT_TRUE(is_CorporateActionsType("redemption"));
    ASSERT_TRUE(is_CorporateActionsType("name_change"));
    ASSERT_TRUE(is_CorporateActionsType("worthless_removal"));
    ASSERT_TRUE(is_CorporateActionsType("rights_distribution"));
    ASSERT_FALSE(is_CorporateActionsType("invalid_type"));
}
