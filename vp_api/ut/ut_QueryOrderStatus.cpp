#include <gtest/gtest.h>
#include "vp/QueryOrderStatus.h"

TEST(QueryOrderStatusTest, ToString) {
    ASSERT_EQ("open", to_str(vp::QueryOrderStatus::open));
    ASSERT_EQ("closed", to_str(vp::QueryOrderStatus::closed));
    ASSERT_EQ("all", to_str(vp::QueryOrderStatus::all));
}

TEST(QueryOrderStatusTest, FromString) {
    ASSERT_EQ(vp::QueryOrderStatus::open, QueryOrderStatus_from_str("open"));
    ASSERT_EQ(vp::QueryOrderStatus::closed, QueryOrderStatus_from_str("closed"));
    ASSERT_EQ(vp::QueryOrderStatus::all, QueryOrderStatus_from_str("all"));
}

TEST(QueryOrderStatusTest, FromStringInvalid) {
    ASSERT_THROW(QueryOrderStatus_from_str("invalid_status"), std::invalid_argument);
}

TEST(QueryOrderStatusTest, IsQueryOrderStatus) {
    ASSERT_TRUE(is_QueryOrderStatus("open"));
    ASSERT_TRUE(is_QueryOrderStatus("closed"));
    ASSERT_TRUE(is_QueryOrderStatus("all"));
    ASSERT_FALSE(is_QueryOrderStatus("invalid_status"));
}
