#include <gtest/gtest.h>
#include "vp/NonTradeActivityStatus.h"

TEST(NonTradeActivityStatusTest, ToString) {
    ASSERT_EQ("executed", to_str(vp::NonTradeActivityStatus::executed));
    ASSERT_EQ("correct", to_str(vp::NonTradeActivityStatus::correct));
    ASSERT_EQ("canceled", to_str(vp::NonTradeActivityStatus::canceled));
}

TEST(NonTradeActivityStatusTest, FromString) {
    ASSERT_EQ(vp::NonTradeActivityStatus::executed, NonTradeActivityStatus_from_str("executed"));
    ASSERT_EQ(vp::NonTradeActivityStatus::correct, NonTradeActivityStatus_from_str("correct"));
    ASSERT_EQ(vp::NonTradeActivityStatus::canceled, NonTradeActivityStatus_from_str("canceled"));
}

TEST(NonTradeActivityStatusTest, FromStringInvalid) {
    ASSERT_THROW(NonTradeActivityStatus_from_str("invalid_status"), std::invalid_argument);
}

TEST(NonTradeActivityStatusTest, IsNonTradeActivityStatus) {
    ASSERT_TRUE(is_NonTradeActivityStatus("executed"));
    ASSERT_TRUE(is_NonTradeActivityStatus("correct"));
    ASSERT_TRUE(is_NonTradeActivityStatus("canceled"));
    ASSERT_FALSE(is_NonTradeActivityStatus("invalid_status"));
}
