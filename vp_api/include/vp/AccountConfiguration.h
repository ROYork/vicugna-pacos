#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <compare>
#include "vp/DTBPCheck.h"
#include "vp/PDTCheck.h"
#include "vp/TradeConfirmationEmail.h"

namespace vp {

/**
 * @brief Represents the account configuration settings
 *
 * See https://docs.alpaca.markets/reference/getaccountconfig
 */
struct AccountConfiguration
{
  DTBPCheck dtbp_check = DTBPCheck::both;
  bool fractional_trading = true;
  std::string max_margin_multiplier = "4";
  bool no_shorting = false;
  PDTCheck pdt_check = PDTCheck::both;
  bool suspend_trade = false;
  TradeConfirmationEmail trade_confirm_email = TradeConfirmationEmail::all;
  bool ptp_no_exception_entry = false;
  std::optional<int> max_options_trading_level;

  std::string to_json() const;
  static AccountConfiguration from_json(const std::string& jsonStr);

  auto operator<=>(const AccountConfiguration& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::AccountConfiguration>
{
  using T = vp::AccountConfiguration;
  static constexpr auto value = glz::object(
    "dtbp_check", &T::dtbp_check,
    "fractional_trading", &T::fractional_trading,
    "max_margin_multiplier", &T::max_margin_multiplier,
    "no_shorting", &T::no_shorting,
    "pdt_check", &T::pdt_check,
    "suspend_trade", &T::suspend_trade,
    "trade_confirm_email", &T::trade_confirm_email,
    "ptp_no_exception_entry", &T::ptp_no_exception_entry,
    "max_options_trading_level", &T::max_options_trading_level
  );
};

inline std::string vp::AccountConfiguration::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::AccountConfiguration vp::AccountConfiguration::from_json(
  const std::string& jsonStr)
{
  vp::AccountConfiguration obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error(
      "Failed to parse AccountConfiguration JSON: " +
      std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
