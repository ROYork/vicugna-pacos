#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <compare>
#include "vp/AssetClass.h"
#include "vp/PositionSide.h"

namespace vp {

/**
 * @brief Represents a position in the Alpaca trading account
 *
 * See https://alpaca.markets/docs/api-references/trading-api/positions/
 */
struct Position
{
  std::string asset_id = "";                     ///< Asset ID
  std::string symbol = "";                       ///< Symbol
  std::string exchange = "";                     ///< Exchange where asset is traded
  AssetClass asset_class = AssetClass::us_equity;///< Asset class
  double avg_entry_price = 0.0;                  ///< Average entry price
  std::string qty = "0";                         ///< Quantity (as string to handle fractional shares)
  PositionSide side = PositionSide::long_;       ///< Long or short
  double market_value = 0.0;                     ///< Current market value
  double cost_basis = 0.0;                       ///< Total cost basis
  double unrealized_pl = 0.0;                    ///< Unrealized profit/loss
  double unrealized_plpc = 0.0;                  ///< Unrealized profit/loss percent
  double unrealized_intraday_pl = 0.0;           ///< Unrealized intraday profit/loss
  double unrealized_intraday_plpc = 0.0;         ///< Unrealized intraday profit/loss percent
  double current_price = 0.0;                    ///< Current asset price
  double lastday_price = 0.0;                    ///< Last day's asset price
  double change_today = 0.0;                     ///< Change percent from last day
  std::string qty_available = "0";               ///< Quantity available for trading

  // Three-way comparison operator for consistency
  std::strong_ordering operator<=>(const Position& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::Position>
{
  using T = vp::Position;
  static constexpr auto value = object(
    "asset_id", &T::asset_id,
    "symbol", &T::symbol,
    "exchange", &T::exchange,
    "asset_class", &T::asset_class,
    "avg_entry_price", &T::avg_entry_price,
    "qty", &T::qty,
    "side", &T::side,
    "market_value", &T::market_value,
    "cost_basis", &T::cost_basis,
    "unrealized_pl", &T::unrealized_pl,
    "unrealized_plpc", &T::unrealized_plpc,
    "unrealized_intraday_pl", &T::unrealized_intraday_pl,
    "unrealized_intraday_plpc", &T::unrealized_intraday_plpc,
    "current_price", &T::current_price,
    "lastday_price", &T::lastday_price,
    "change_today", &T::change_today,
    "qty_available", &T::qty_available
  );
};
