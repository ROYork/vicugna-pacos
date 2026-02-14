#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <compare>
#include "vp/OrderType.h"
#include "vp/OrderSide.h"
#include "vp/TimeInForce.h"
#include "vp/OrderStatus.h"
#include "vp/OrderClass.h"
#include "vp/AssetClass.h"

namespace vp {

/**
 * @brief Represents an order in the Alpaca trading system
 *
 * See https://alpaca.markets/docs/api-references/trading-api/orders/
 */
struct Order
{
  std::string id = "";                              ///< Order ID
  std::string client_order_id = "";                 ///< Client-specified unique order ID
  std::string created_at = "";                      ///< Timestamp when order was created
  std::string updated_at = "";                      ///< Timestamp when order was last updated
  std::string submitted_at = "";                    ///< Timestamp when order was submitted
  std::optional<std::string> filled_at;             ///< Timestamp when order was filled
  std::optional<std::string> expired_at;            ///< Timestamp when order expired
  std::optional<std::string> canceled_at;           ///< Timestamp when order was canceled
  std::optional<std::string> failed_at;             ///< Timestamp when order failed
  std::optional<std::string> replaced_at;           ///< Timestamp when order was replaced
  std::optional<std::string> replaced_by;           ///< Order ID that replaced this order
  std::optional<std::string> replaces;              ///< Order ID that this order replaces
  AssetClass asset_class = AssetClass::us_equity;   ///< Asset class
  std::string asset_id = "";                        ///< Asset ID
  std::string symbol = "";                          ///< Symbol
  std::string qty = "0";                            ///< Quantity (as string to handle fractional shares)
  std::optional<std::string> notional;              ///< Dollar amount (for fractional/notional orders)
  std::string filled_qty = "0";                     ///< Filled quantity
  std::optional<double> filled_avg_price;           ///< Average fill price
  OrderClass order_class = OrderClass::simple;      ///< Order class (simple, bracket, oco, oto)
  OrderType order_type = OrderType::market;         ///< Order type (market, limit, stop, etc.)
  OrderSide side = OrderSide::buy;                  ///< Buy or sell
  TimeInForce time_in_force = TimeInForce::day;     ///< Time in force
  std::optional<double> limit_price;                ///< Limit price (for limit orders)
  std::optional<double> stop_price;                 ///< Stop price (for stop orders)
  OrderStatus status = OrderStatus::new_;           ///< Order status
  bool extended_hours = false;                      ///< If true, eligible for execution outside regular trading hours
  // Legs for multi-leg orders (bracket, oco, oto)
  // std::optional<std::vector<Order>> legs;        // Could add this for complex orders

  // Three-way comparison operator for consistency
  std::strong_ordering operator<=>(const Order& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::Order>
{
  using T = vp::Order;
  static constexpr auto value = object(
    "id", &T::id,
    "client_order_id", &T::client_order_id,
    "created_at", &T::created_at,
    "updated_at", &T::updated_at,
    "submitted_at", &T::submitted_at,
    "filled_at", &T::filled_at,
    "expired_at", &T::expired_at,
    "canceled_at", &T::canceled_at,
    "failed_at", &T::failed_at,
    "replaced_at", &T::replaced_at,
    "replaced_by", &T::replaced_by,
    "replaces", &T::replaces,
    "asset_class", &T::asset_class,
    "asset_id", &T::asset_id,
    "symbol", &T::symbol,
    "qty", &T::qty,
    "notional", &T::notional,
    "filled_qty", &T::filled_qty,
    "filled_avg_price", &T::filled_avg_price,
    "order_class", &T::order_class,
    "order_type", &T::order_type,
    "side", &T::side,
    "time_in_force", &T::time_in_force,
    "limit_price", &T::limit_price,
    "stop_price", &T::stop_price,
    "status", &T::status,
    "extended_hours", &T::extended_hours
  );
};
