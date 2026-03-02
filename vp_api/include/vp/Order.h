#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include <compare>
#include "vp/OrderType.h"
#include "vp/OrderSide.h"
#include "vp/TimeInForce.h"
#include "vp/OrderStatus.h"
#include "vp/OrderClass.h"
#include "vp/AssetClass.h"
#include "vp/PositionIntent.h"

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
  std::optional<std::string> expires_at;            ///< When the order expires
  AssetClass asset_class = AssetClass::us_equity;   ///< Asset class
  std::string asset_id = "";                        ///< Asset ID
  std::string symbol = "";                          ///< Symbol
  std::string qty = "0";                            ///< Quantity (string for fractional)
  std::optional<std::string> notional;              ///< Dollar amount (fractional/notional)
  std::string filled_qty = "0";                     ///< Filled quantity
  std::optional<double> filled_avg_price;           ///< Average fill price
  OrderClass order_class = OrderClass::simple;      ///< Order class
  OrderType order_type = OrderType::market;         ///< Order type
  OrderSide side = OrderSide::buy;                  ///< Buy or sell
  TimeInForce time_in_force = TimeInForce::day;     ///< Time in force
  std::optional<double> limit_price;                ///< Limit price
  std::optional<double> stop_price;                 ///< Stop price
  std::optional<double> trail_percent;              ///< Trailing stop percent
  std::optional<double> trail_price;                ///< Trailing stop price
  std::optional<double> hwm;                        ///< High water mark
  OrderStatus status = OrderStatus::new_;           ///< Order status
  bool extended_hours = false;                      ///< Eligible outside regular hours
  std::optional<PositionIntent> position_intent;    ///< Position intent for options
  std::optional<std::string> ratio_qty;             ///< Ratio quantity for mleg
  std::optional<std::vector<Order>> legs;           ///< Legs for multi-leg orders

  // Custom comparison (recursive type prevents defaulted <=>)
  bool operator==(const Order& other) const
  {
    return id == other.id
        && client_order_id == other.client_order_id
        && symbol == other.symbol
        && status == other.status;
  }

  std::strong_ordering operator<=>(const Order& other) const
  {
    if (auto cmp = id <=> other.id; cmp != 0)
    {
      return cmp;
    }
    return client_order_id <=> other.client_order_id;
  }
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
    "expires_at", &T::expires_at,
    "asset_class", &T::asset_class,
    "asset_id", &T::asset_id,
    "symbol", &T::symbol,
    "qty", &T::qty,
    "notional", &T::notional,
    "filled_qty", &T::filled_qty,
    "filled_avg_price", &T::filled_avg_price,
    "order_class", &T::order_class,
    "type", &T::order_type,
    "side", &T::side,
    "time_in_force", &T::time_in_force,
    "limit_price", &T::limit_price,
    "stop_price", &T::stop_price,
    "trail_percent", &T::trail_percent,
    "trail_price", &T::trail_price,
    "hwm", &T::hwm,
    "status", &T::status,
    "extended_hours", &T::extended_hours,
    "position_intent", &T::position_intent,
    "ratio_qty", &T::ratio_qty,
    "legs", &T::legs
  );
};
