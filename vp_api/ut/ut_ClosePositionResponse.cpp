#include <gtest/gtest.h>
#include "vp/ClosePositionResponse.h"
#include <glaze/glaze.hpp>

TEST(ClosePositionResponseTest, DefaultConstruction)
{
  vp::ClosePositionResponse response;

  ASSERT_TRUE(response.symbol.empty());
  ASSERT_EQ(0, response.status);
  ASSERT_TRUE(response.body.str.empty());
}

TEST(ClosePositionResponseTest, ParameterizedConstruction)
{
  vp::Order order{
    .id = "order-close-001",
    .client_order_id = "client-close-001",
    .symbol = "GOOG",
    .qty = "5",
    .order_type = vp::OrderType::market,
    .side = vp::OrderSide::sell,
    .status = vp::OrderStatus::filled
  };

  std::string order_json;
  (void)glz::write_json(order, order_json);

  vp::ClosePositionResponse response{
    .symbol = "GOOG",
    .status = 200,
    .body = glz::raw_json{order_json}
  };

  ASSERT_EQ("GOOG", response.symbol);
  ASSERT_EQ(200, response.status);

  auto parsed_order = response.get_order();
  ASSERT_TRUE(parsed_order.has_value());
  ASSERT_EQ("order-close-001", parsed_order->id);
  ASSERT_EQ("GOOG", parsed_order->symbol);
  ASSERT_EQ(vp::OrderStatus::filled, parsed_order->status);
}

TEST(ClosePositionResponseTest, ErrorBodyReturnsNulloptFromGetOrder)
{
  std::string error_body = R"({"code":40310000,"message":"position not found"})";

  vp::ClosePositionResponse response{
    .symbol = "INVALID",
    .status = 404,
    .body = glz::raw_json{error_body}
  };

  auto parsed_order = response.get_order();
  ASSERT_FALSE(parsed_order.has_value());
}

TEST(ClosePositionResponseTest, GlazeRoundTrip)
{
  vp::Order order{
    .id = "order-rt-close-001",
    .client_order_id = "client-rt-close-001",
    .created_at = "2024-02-20T14:00:00Z",
    .symbol = "TSLA",
    .qty = "15",
    .order_type = vp::OrderType::market,
    .side = vp::OrderSide::sell,
    .time_in_force = vp::TimeInForce::day,
    .status = vp::OrderStatus::filled
  };

  std::string order_json;
  (void)glz::write_json(order, order_json);

  vp::ClosePositionResponse original{
    .symbol = "TSLA",
    .status = 200,
    .body = glz::raw_json{order_json}
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::ClosePositionResponse deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.symbol, deserialized.symbol);
  ASSERT_EQ(original.status, deserialized.status);
  ASSERT_EQ(original.body.str, deserialized.body.str);

  auto orig_order = original.get_order();
  auto deser_order = deserialized.get_order();
  ASSERT_TRUE(orig_order.has_value());
  ASSERT_TRUE(deser_order.has_value());
  ASSERT_EQ(orig_order->id, deser_order->id);
  ASSERT_EQ(orig_order->symbol, deser_order->symbol);
  ASSERT_EQ(orig_order->status, deser_order->status);
}
