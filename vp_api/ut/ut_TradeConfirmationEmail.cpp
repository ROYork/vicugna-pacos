#include <gtest/gtest.h>
#include "vp/TradeConfirmationEmail.h"

TEST(TradeConfirmationEmailTest, ToString) {
    ASSERT_EQ("all", to_str(vp::TradeConfirmationEmail::all));
    ASSERT_EQ("none", to_str(vp::TradeConfirmationEmail::none));
}

TEST(TradeConfirmationEmailTest, FromString) {
    ASSERT_EQ(vp::TradeConfirmationEmail::all, TradeConfirmationEmail_from_str("all"));
    ASSERT_EQ(vp::TradeConfirmationEmail::none, TradeConfirmationEmail_from_str("none"));
}

TEST(TradeConfirmationEmailTest, FromStringInvalid) {
    ASSERT_THROW(TradeConfirmationEmail_from_str("invalid_email_type"), std::invalid_argument);
}

TEST(TradeConfirmationEmailTest, IsTradeConfirmationEmail) {
    ASSERT_TRUE(is_TradeConfirmationEmail("all"));
    ASSERT_TRUE(is_TradeConfirmationEmail("none"));
    ASSERT_FALSE(is_TradeConfirmationEmail("invalid_email_type"));
}
