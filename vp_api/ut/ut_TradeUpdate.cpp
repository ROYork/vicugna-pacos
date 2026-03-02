#include <gtest/gtest.h>
#include "vp/TradeUpdate.h"
#include <glaze/glaze.hpp>

TEST(TradeUpdateTest, DefaultConstruction)
{
  vp::TradeUpdate update;

  ASSERT_EQ(vp::TradeEvent::new_, update.event);
  ASSERT_FALSE(update.execution_id.has_value());
  ASSERT_FALSE(update.timestamp.has_value());
  ASSERT_FALSE(update.position_qty.has_value());
  ASSERT_FALSE(update.price.has_value());
  ASSERT_FALSE(update.qty.has_value());
}

TEST(TradeUpdateTest, ParameterizedConstruction)
{
  vp::Order order{
    .id = "order-tu-001",
    .client_order_id = "client-tu-001",
    .symbol = "AAPL",
    .qty = "10",
    .order_type = vp::OrderType::limit,
    .side = vp::OrderSide::buy,
    .time_in_force = vp::TimeInForce::day,
    .status = vp::OrderStatus::filled
  };

  vp::TradeUpdate update{
    .event = vp::TradeEvent::fill,
    .execution_id = "exec-001",
    .order = order,
    .timestamp = "2024-01-15T10:30:00Z",
    .position_qty = "10",
    .price = "175.50",
    .qty = "10"
  };

  ASSERT_EQ(vp::TradeEvent::fill, update.event);
  ASSERT_TRUE(update.execution_id.has_value());
  ASSERT_EQ("exec-001", update.execution_id.value());
  ASSERT_EQ("order-tu-001", update.order.id);
  ASSERT_EQ("AAPL", update.order.symbol);
  ASSERT_EQ(vp::OrderStatus::filled, update.order.status);
  ASSERT_TRUE(update.timestamp.has_value());
  ASSERT_EQ("2024-01-15T10:30:00Z", update.timestamp.value());
  ASSERT_TRUE(update.position_qty.has_value());
  ASSERT_EQ("10", update.position_qty.value());
  ASSERT_TRUE(update.price.has_value());
  ASSERT_EQ("175.50", update.price.value());
  ASSERT_TRUE(update.qty.has_value());
  ASSERT_EQ("10", update.qty.value());
}

TEST(TradeUpdateTest, GlazeRoundTrip)
{
  vp::Order order{
    .id = "order-rt-tu-001",
    .client_order_id = "client-rt-tu-001",
    .created_at = "2024-03-10T09:30:00Z",
    .symbol = "MSFT",
    .qty = "5",
    .order_type = vp::OrderType::market,
    .side = vp::OrderSide::sell,
    .time_in_force = vp::TimeInForce::day,
    .status = vp::OrderStatus::filled
  };

  vp::TradeUpdate original{
    .event = vp::TradeEvent::partial_fill,
    .execution_id = "exec-rt-001",
    .order = order,
    .timestamp = "2024-03-10T09:31:00Z",
    .position_qty = "3",
    .price = "420.25",
    .qty = "2"
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::TradeUpdate deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.event, deserialized.event);
  ASSERT_EQ(original.execution_id, deserialized.execution_id);
  ASSERT_EQ(original.order.id, deserialized.order.id);
  ASSERT_EQ(original.order.symbol, deserialized.order.symbol);
  ASSERT_EQ(original.order.status, deserialized.order.status);
  ASSERT_EQ(original.timestamp, deserialized.timestamp);
  ASSERT_EQ(original.position_qty, deserialized.position_qty);
  ASSERT_EQ(original.price, deserialized.price);
  ASSERT_EQ(original.qty, deserialized.qty);
}
