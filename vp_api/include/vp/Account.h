#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <iostream>
#include "AccountStatus.h"

namespace vp {

/**
 * @brief Represents an Alpaca trading account
 *
 * See https://alpaca.markets/docs/api-references/trading-api/account/
 */
struct Account
{
  std::string id = "";                      ///< Account ID
  std::string account_number = "";          ///< Account number
  AccountStatus status = AccountStatus::ACTIVE;  ///< Account status
  std::string currency = "";                ///< USD
  double buying_power = 0.0;                 ///< Current available buying power
  double regt_buying_power = 0.0;            ///< RegT buying power
  double daytrading_buying_power = 0.0;      ///< Day trading buying power
  double non_marginable_buying_power = 0.0;  ///< Non-marginable buying power
  double cash = 0.0;                         ///< Cash balance
  double accrued_fees = 0.0;                 ///< Accrued fees
  double portfolio_value = 0.0;              ///< Total portfolio value
  bool pattern_day_trader = false;           ///< Whether account is flagged as PDT
  bool trading_blocked = false;              ///< If true, account is not allowed to place orders
  bool transfers_blocked = false;            ///< If true, account is not allowed to request money transfers
  bool account_blocked = false;              ///< If true, account activity is prohibited
  bool trade_suspended_by_user = false;      ///< If true, account is suspended
  int multiplier = 0;                        ///< Multiplier for buying power
  bool shorting_enabled = false;             ///< If true, account can short
  double equity = 0.0;                       ///< Account equity (cash + long_market_value + short_market_value)
  double last_equity = 0.0;                  ///< Equity as of previous trading day
  double long_market_value = 0.0;            ///< Long market value
  double short_market_value = 0.0;           ///< Short market value
  double initial_margin = 0.0;               ///< Initial margin requirement
  double maintenance_margin = 0.0;           ///< Maintenance margin requirement
  double last_maintenance_margin = 0.0;      ///< Maintenance margin as of previous trading day
  double sma = 0.0;                          ///< Special Memorandum Account (SMA) value
  int daytrade_count = 0;                    ///< Number of day trades in last 5 trading days
  std::string created_at = "";               ///< Timestamp of account creation

  std::string to_json() const;
  static Account from_json(const std::string &jsonStr);

  // Three-way comparison operator
  std::strong_ordering operator<=>(const Account& other) const = default;
};

} // namespace vp

// Outside of alpaca namespace
template <>
struct glz::meta<vp::Account>
{
  using T = vp::Account;
  static constexpr auto value = glz::object(
    "id", &T::id,
    "account_number", &T::account_number,
    "status", &T::status,
    "currency", &T::currency,
    "buying_power", &T::buying_power,
    "regt_buying_power", &T::regt_buying_power,
    "daytrading_buying_power", &T::daytrading_buying_power,
    "non_marginable_buying_power", &T::non_marginable_buying_power,
    "cash", &T::cash,
    "accrued_fees", &T::accrued_fees,
    "portfolio_value", &T::portfolio_value,
    "pattern_day_trader", &T::pattern_day_trader,
    "trading_blocked", &T::trading_blocked,
    "transfers_blocked", &T::transfers_blocked,
    "account_blocked", &T::account_blocked,
    "trade_suspended_by_user", &T::trade_suspended_by_user,
    "multiplier", &T::multiplier,
    "shorting_enabled", &T::shorting_enabled,
    "equity", &T::equity,
    "last_equity", &T::last_equity,
    "long_market_value", &T::long_market_value,
    "short_market_value", &T::short_market_value,
    "initial_margin", &T::initial_margin,
    "maintenance_margin", &T::maintenance_margin,
    "last_maintenance_margin", &T::last_maintenance_margin,
    "sma", &T::sma,
    "daytrade_count", &T::daytrade_count,
    "created_at", &T::created_at
  );
};

/**
 * @brief Converts this class to json
 */
inline std::string vp::Account::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    std::cerr << "error:" << __FUNCTION__
              << " json conversion failed with error: " << error;
    return std::string("");
  }
  else
  {
    return json_string;
  }
}

/**
 * @brief Creates a \c Account class from a JSON string
 */
inline vp::Account vp::Account::from_json(const std::string &jsonStr)
{
  vp::Account obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse Account JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
