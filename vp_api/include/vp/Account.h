#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <iostream>
#include <cctype>
#include <stdexcept>
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

namespace detail {

struct AccountWire
{
  std::string id = "";
  std::string account_number = "";
  AccountStatus status = AccountStatus::ACTIVE;
  std::string currency = "";
  glz::raw_json buying_power = {};
  glz::raw_json regt_buying_power = {};
  glz::raw_json daytrading_buying_power = {};
  glz::raw_json non_marginable_buying_power = {};
  glz::raw_json cash = {};
  glz::raw_json accrued_fees = {};
  glz::raw_json portfolio_value = {};
  bool pattern_day_trader = false;
  bool trading_blocked = false;
  bool transfers_blocked = false;
  bool account_blocked = false;
  bool trade_suspended_by_user = false;
  glz::raw_json multiplier = {};
  bool shorting_enabled = false;
  glz::raw_json equity = {};
  glz::raw_json last_equity = {};
  glz::raw_json long_market_value = {};
  glz::raw_json short_market_value = {};
  glz::raw_json initial_margin = {};
  glz::raw_json maintenance_margin = {};
  glz::raw_json last_maintenance_margin = {};
  glz::raw_json sma = {};
  glz::raw_json daytrade_count = {};
  std::string created_at = "";
};

} // namespace detail

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

template <>
struct glz::meta<vp::detail::AccountWire>
{
  using T = vp::detail::AccountWire;
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
  if (!ec)
  {
    return obj;
  }

  // Alpaca frequently returns numeric account fields as quoted strings.
  // Parse via a tolerant wire format when strict typed parsing fails.
  auto trim = [](std::string_view in) -> std::string_view {
    size_t start = 0;
    while (start < in.size() &&
           std::isspace(static_cast<unsigned char>(in[start])))
    {
      ++start;
    }
    size_t end = in.size();
    while (end > start &&
           std::isspace(static_cast<unsigned char>(in[end - 1])))
    {
      --end;
    }
    return in.substr(start, end - start);
  };

  auto unquote = [&](std::string_view in) -> std::string {
    auto s = trim(in);
    if (s.size() >= 2 && s.front() == '"' && s.back() == '"')
    {
      s.remove_prefix(1);
      s.remove_suffix(1);
    }
    return std::string(s);
  };

  auto parse_double = [&](const glz::raw_json& raw, const char* field) -> double {
    try
    {
      const std::string value = unquote(raw.str);
      return std::stod(value);
    }
    catch (const std::exception&)
    {
      throw std::runtime_error(std::string("Failed to parse Account field '") +
                               field + "' from value: " + std::string(raw.str));
    }
  };

  auto parse_int = [&](const glz::raw_json& raw, const char* field) -> int {
    try
    {
      const std::string value = unquote(raw.str);
      return std::stoi(value);
    }
    catch (const std::exception&)
    {
      throw std::runtime_error(std::string("Failed to parse Account field '") +
                               field + "' from value: " + std::string(raw.str));
    }
  };

  vp::detail::AccountWire wire;
  auto wire_ec = glz::read_json(wire, jsonStr);
  if (wire_ec)
  {
    throw std::runtime_error("Failed to parse Account JSON: " +
                             std::to_string(static_cast<int>(wire_ec)));
  }

  obj.id = wire.id;
  obj.account_number = wire.account_number;
  obj.status = wire.status;
  obj.currency = wire.currency;
  obj.buying_power = parse_double(wire.buying_power, "buying_power");
  obj.regt_buying_power = parse_double(wire.regt_buying_power, "regt_buying_power");
  obj.daytrading_buying_power = parse_double(wire.daytrading_buying_power, "daytrading_buying_power");
  obj.non_marginable_buying_power = parse_double(wire.non_marginable_buying_power, "non_marginable_buying_power");
  obj.cash = parse_double(wire.cash, "cash");
  obj.accrued_fees = parse_double(wire.accrued_fees, "accrued_fees");
  obj.portfolio_value = parse_double(wire.portfolio_value, "portfolio_value");
  obj.pattern_day_trader = wire.pattern_day_trader;
  obj.trading_blocked = wire.trading_blocked;
  obj.transfers_blocked = wire.transfers_blocked;
  obj.account_blocked = wire.account_blocked;
  obj.trade_suspended_by_user = wire.trade_suspended_by_user;
  obj.multiplier = parse_int(wire.multiplier, "multiplier");
  obj.shorting_enabled = wire.shorting_enabled;
  obj.equity = parse_double(wire.equity, "equity");
  obj.last_equity = parse_double(wire.last_equity, "last_equity");
  obj.long_market_value = parse_double(wire.long_market_value, "long_market_value");
  obj.short_market_value = parse_double(wire.short_market_value, "short_market_value");
  obj.initial_margin = parse_double(wire.initial_margin, "initial_margin");
  obj.maintenance_margin = parse_double(wire.maintenance_margin, "maintenance_margin");
  obj.last_maintenance_margin = parse_double(wire.last_maintenance_margin, "last_maintenance_margin");
  obj.sma = parse_double(wire.sma, "sma");
  obj.daytrade_count = parse_int(wire.daytrade_count, "daytrade_count");
  obj.created_at = wire.created_at;
  return obj;
}
