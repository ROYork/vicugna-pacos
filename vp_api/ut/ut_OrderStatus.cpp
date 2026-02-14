#include <gtest/gtest.h>
#include "vp/OrderStatus.h"

TEST(OrderStatusTest, ToString) {
    ASSERT_EQ("new", to_str(vp::OrderStatus::new_));
    ASSERT_EQ("partially_filled", to_str(vp::OrderStatus::partially_filled));
    ASSERT_EQ("filled", to_str(vp::OrderStatus::filled));
    ASSERT_EQ("done_for_day", to_str(vp::OrderStatus::done_for_day));
    ASSERT_EQ("canceled", to_str(vp::OrderStatus::canceled));
    ASSERT_EQ("expired", to_str(vp::OrderStatus::expired));
    ASSERT_EQ("replaced", to_str(vp::OrderStatus::replaced));
    ASSERT_EQ("pending_cancel", to_str(vp::OrderStatus::pending_cancel));
    ASSERT_EQ("pending_replace", to_str(vp::OrderStatus::pending_replace));
    ASSERT_EQ("pending_review", to_str(vp::OrderStatus::pending_review));
    ASSERT_EQ("accepted", to_str(vp::OrderStatus::accepted));
    ASSERT_EQ("pending_new", to_str(vp::OrderStatus::pending_new));
    ASSERT_EQ("accepted_for_bidding", to_str(vp::OrderStatus::accepted_for_bidding));
    ASSERT_EQ("stopped", to_str(vp::OrderStatus::stopped));
    ASSERT_EQ("rejected", to_str(vp::OrderStatus::rejected));
    ASSERT_EQ("suspended", to_str(vp::OrderStatus::suspended));
    ASSERT_EQ("calculated", to_str(vp::OrderStatus::calculated));
    ASSERT_EQ("held", to_str(vp::OrderStatus::held));
}

TEST(OrderStatusTest, FromString) {
    ASSERT_EQ(vp::OrderStatus::new_, OrderStatus_from_str("new"));
    ASSERT_EQ(vp::OrderStatus::partially_filled, OrderStatus_from_str("partially_filled"));
    ASSERT_EQ(vp::OrderStatus::filled, OrderStatus_from_str("filled"));
    ASSERT_EQ(vp::OrderStatus::done_for_day, OrderStatus_from_str("done_for_day"));
    ASSERT_EQ(vp::OrderStatus::canceled, OrderStatus_from_str("canceled"));
    ASSERT_EQ(vp::OrderStatus::expired, OrderStatus_from_str("expired"));
    ASSERT_EQ(vp::OrderStatus::replaced, OrderStatus_from_str("replaced"));
    ASSERT_EQ(vp::OrderStatus::pending_cancel, OrderStatus_from_str("pending_cancel"));
    ASSERT_EQ(vp::OrderStatus::pending_replace, OrderStatus_from_str("pending_replace"));
    ASSERT_EQ(vp::OrderStatus::pending_review, OrderStatus_from_str("pending_review"));
    ASSERT_EQ(vp::OrderStatus::accepted, OrderStatus_from_str("accepted"));
    ASSERT_EQ(vp::OrderStatus::pending_new, OrderStatus_from_str("pending_new"));
    ASSERT_EQ(vp::OrderStatus::accepted_for_bidding, OrderStatus_from_str("accepted_for_bidding"));
    ASSERT_EQ(vp::OrderStatus::stopped, OrderStatus_from_str("stopped"));
    ASSERT_EQ(vp::OrderStatus::rejected, OrderStatus_from_str("rejected"));
    ASSERT_EQ(vp::OrderStatus::suspended, OrderStatus_from_str("suspended"));
    ASSERT_EQ(vp::OrderStatus::calculated, OrderStatus_from_str("calculated"));
    ASSERT_EQ(vp::OrderStatus::held, OrderStatus_from_str("held"));
}

TEST(OrderStatusTest, FromStringInvalid) {
    ASSERT_THROW(OrderStatus_from_str("invalid_status"), std::invalid_argument);
}

TEST(OrderStatusTest, IsOrderStatus) {
    ASSERT_TRUE(is_OrderStatus("new"));
    ASSERT_TRUE(is_OrderStatus("partially_filled"));
    ASSERT_TRUE(is_OrderStatus("filled"));
    ASSERT_TRUE(is_OrderStatus("done_for_day"));
    ASSERT_TRUE(is_OrderStatus("canceled"));
    ASSERT_TRUE(is_OrderStatus("expired"));
    ASSERT_TRUE(is_OrderStatus("replaced"));
    ASSERT_TRUE(is_OrderStatus("pending_cancel"));
    ASSERT_TRUE(is_OrderStatus("pending_replace"));
    ASSERT_TRUE(is_OrderStatus("pending_review"));
    ASSERT_TRUE(is_OrderStatus("accepted"));
    ASSERT_TRUE(is_OrderStatus("pending_new"));
    ASSERT_TRUE(is_OrderStatus("accepted_for_bidding"));
    ASSERT_TRUE(is_OrderStatus("stopped"));
    ASSERT_TRUE(is_OrderStatus("rejected"));
    ASSERT_TRUE(is_OrderStatus("suspended"));
    ASSERT_TRUE(is_OrderStatus("calculated"));
    ASSERT_TRUE(is_OrderStatus("held"));
    ASSERT_FALSE(is_OrderStatus("invalid_status"));
}
