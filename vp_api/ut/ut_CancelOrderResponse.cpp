#include <gtest/gtest.h>
#include "vp/CancelOrderResponse.h"
#include <glaze/glaze.hpp>

TEST(CancelOrderResponseTest, DefaultConstruction)
{
  vp::CancelOrderResponse response;

  ASSERT_EQ(0, response.status);
  ASSERT_TRUE(response.id.empty());
  ASSERT_TRUE(response.body.str.empty());
}

TEST(CancelOrderResponseTest, ParameterizedConstruction)
{
  vp::Order order{
    .id = "order-cancel-001",
    .client_order_id = "client-cancel-001",
    .symbol = "AAPL",
    .status = vp::OrderStatus::canceled
  };

  std::string order_json;
  (void)glz::write_json(order, order_json);

  vp::CancelOrderResponse response{
    .status = 200,
    .id = "cancel-resp-001",
    .body = glz::raw_json{order_json}
  };

  ASSERT_EQ(200, response.status);
  ASSERT_EQ("cancel-resp-001", response.id);

  auto parsed_order = response.get_order();
  ASSERT_TRUE(parsed_order.has_value());
  ASSERT_EQ("order-cancel-001", parsed_order->id);
  ASSERT_EQ("AAPL", parsed_order->symbol);
  ASSERT_EQ(vp::OrderStatus::canceled, parsed_order->status);
}

TEST(CancelOrderResponseTest, ErrorBodyReturnsNulloptFromGetOrder)
{
  // Simulate a 207 error body with code/message instead of Order
  std::string error_body = R"({"code":40310000,"message":"order is not cancelable"})";

  vp::CancelOrderResponse response{
    .status = 422,
    .id = "cancel-fail-001",
    .body = glz::raw_json{error_body}
  };

  auto parsed_order = response.get_order();
  ASSERT_FALSE(parsed_order.has_value());
}

TEST(CancelOrderResponseTest, GlazeRoundTrip)
{
  vp::Order order{
    .id = "order-rt-001",
    .client_order_id = "client-rt-001",
    .created_at = "2024-01-15T10:30:00Z",
    .symbol = "MSFT",
    .qty = "10",
    .order_type = vp::OrderType::market,
    .side = vp::OrderSide::buy,
    .time_in_force = vp::TimeInForce::day,
    .status = vp::OrderStatus::canceled
  };

  std::string order_json;
  (void)glz::write_json(order, order_json);

  vp::CancelOrderResponse original{
    .status = 200,
    .id = "cancel-rt-001",
    .body = glz::raw_json{order_json}
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::CancelOrderResponse deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.status, deserialized.status);
  ASSERT_EQ(original.id, deserialized.id);
  ASSERT_EQ(original.body.str, deserialized.body.str);

  auto orig_order = original.get_order();
  auto deser_order = deserialized.get_order();
  ASSERT_TRUE(orig_order.has_value());
  ASSERT_TRUE(deser_order.has_value());
  ASSERT_EQ(orig_order->id, deser_order->id);
  ASSERT_EQ(orig_order->symbol, deser_order->symbol);
  ASSERT_EQ(orig_order->status, deser_order->status);
}
