#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include "vp/OrderSide.h"
#include "vp/OrderType.h"
#include "vp/TimeInForce.h"
#include "vp/OrderClass.h"
#include "vp/PositionIntent.h"

namespace vp {

/**
 * @brief Take profit parameters for bracket orders
 */
struct TakeProfitRequest
{
  double limit_price = 0.0;
};

/**
 * @brief Stop loss parameters for bracket orders
 */
struct StopLossRequest
{
  double stop_price = 0.0;
  std::optional<double> limit_price;
};

/**
 * @brief Option leg for multi-leg orders
 */
struct OptionLegRequest
{
  std::string symbol = "";
  std::string qty = "0";
  OrderSide side = OrderSide::buy;
  std::optional<std::string> ratio_qty;
  std::optional<PositionIntent> position_intent;
};

/**
 * @brief Request parameters for submitting a new order
 */
struct OrderRequest
{
  std::string symbol = "";
  std::optional<std::string> qty;
  std::optional<std::string> notional;
  OrderSide side = OrderSide::buy;
  OrderType type = OrderType::market;
  TimeInForce time_in_force = TimeInForce::day;
  std::optional<OrderClass> order_class;
  bool extended_hours = false;
  std::optional<std::string> client_order_id;
  std::optional<double> limit_price;
  std::optional<double> stop_price;
  std::optional<double> trail_price;
  std::optional<double> trail_percent;
  std::optional<std::vector<OptionLegRequest>> legs;
  std::optional<TakeProfitRequest> take_profit;
  std::optional<StopLossRequest> stop_loss;
  std::optional<PositionIntent> position_intent;

  std::string to_json() const
  {
    std::string json_string{};
    auto error = glz::write_json(*this, json_string);
    if (error)
    {
      return "{}";
    }
    return json_string;
  }

  /// Create a market order
  static OrderRequest market(const std::string& sym,
                             const std::string& quantity,
                             OrderSide s)
  {
    return OrderRequest{
      .symbol = sym,
      .qty = quantity,
      .side = s,
      .type = OrderType::market,
      .time_in_force = TimeInForce::day
    };
  }

  /// Create a limit order
  static OrderRequest limit(const std::string& sym,
                            const std::string& quantity,
                            OrderSide s,
                            double price)
  {
    return OrderRequest{
      .symbol = sym,
      .qty = quantity,
      .side = s,
      .type = OrderType::limit,
      .time_in_force = TimeInForce::day,
      .limit_price = price
    };
  }

  /// Create a stop order
  static OrderRequest stop(const std::string& sym,
                           const std::string& quantity,
                           OrderSide s,
                           double price)
  {
    return OrderRequest{
      .symbol = sym,
      .qty = quantity,
      .side = s,
      .type = OrderType::stop,
      .time_in_force = TimeInForce::day,
      .stop_price = price
    };
  }

  /// Create a stop-limit order
  static OrderRequest stop_limit(const std::string& sym,
                                 const std::string& quantity,
                                 OrderSide s,
                                 double stop_px,
                                 double limit_px)
  {
    return OrderRequest{
      .symbol = sym,
      .qty = quantity,
      .side = s,
      .type = OrderType::stop_limit,
      .time_in_force = TimeInForce::day,
      .limit_price = limit_px,
      .stop_price = stop_px
    };
  }

  /// Create a trailing stop order
  static OrderRequest trailing_stop(const std::string& sym,
                                    const std::string& quantity,
                                    OrderSide s,
                                    std::optional<double> trail_px = {},
                                    std::optional<double> trail_pct = {})
  {
    return OrderRequest{
      .symbol = sym,
      .qty = quantity,
      .side = s,
      .type = OrderType::trailing_stop,
      .time_in_force = TimeInForce::day,
      .trail_price = trail_px,
      .trail_percent = trail_pct
    };
  }
};

} // namespace vp

template <>
struct glz::meta<vp::TakeProfitRequest>
{
  using T = vp::TakeProfitRequest;
  static constexpr auto value = glz::object(
    "limit_price", &T::limit_price
  );
};

template <>
struct glz::meta<vp::StopLossRequest>
{
  using T = vp::StopLossRequest;
  static constexpr auto value = glz::object(
    "stop_price", &T::stop_price,
    "limit_price", &T::limit_price
  );
};

template <>
struct glz::meta<vp::OptionLegRequest>
{
  using T = vp::OptionLegRequest;
  static constexpr auto value = glz::object(
    "symbol", &T::symbol,
    "qty", &T::qty,
    "side", &T::side,
    "ratio_qty", &T::ratio_qty,
    "position_intent", &T::position_intent
  );
};

template <>
struct glz::meta<vp::OrderRequest>
{
  using T = vp::OrderRequest;
  static constexpr auto value = glz::object(
    "symbol", &T::symbol,
    "qty", &T::qty,
    "notional", &T::notional,
    "side", &T::side,
    "type", &T::type,
    "time_in_force", &T::time_in_force,
    "order_class", &T::order_class,
    "extended_hours", &T::extended_hours,
    "client_order_id", &T::client_order_id,
    "limit_price", &T::limit_price,
    "stop_price", &T::stop_price,
    "trail_price", &T::trail_price,
    "trail_percent", &T::trail_percent,
    "legs", &T::legs,
    "take_profit", &T::take_profit,
    "stop_loss", &T::stop_loss,
    "position_intent", &T::position_intent
  );
};
