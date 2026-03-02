#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include <compare>
#include "vp/AssetStatus.h"
#include "vp/ContractType.h"
#include "vp/ExerciseStyle.h"

namespace vp {

/**
 * @brief Represents an option contract
 *
 * See https://docs.alpaca.markets/reference/optioncontracts
 */
struct OptionContract
{
  std::string id = "";
  std::string symbol = "";
  std::string name = "";
  AssetStatus status = AssetStatus::active;
  bool tradable = false;
  std::string expiration_date = "";
  std::optional<std::string> root_symbol;
  std::string underlying_symbol = "";
  std::string underlying_asset_id = "";
  ContractType type = ContractType::call;
  ExerciseStyle style = ExerciseStyle::american;
  std::string strike_price = "0";
  std::string size = "100";
  std::optional<std::string> open_interest;
  std::optional<std::string> open_interest_date;
  std::optional<std::string> close_price;
  std::optional<std::string> close_price_date;

  std::string to_json() const;
  static OptionContract from_json(const std::string& jsonStr);

  auto operator<=>(const OptionContract& other) const = default;
};

/**
 * @brief Response wrapper for option contracts listing
 */
struct OptionContractsResponse
{
  std::optional<std::vector<OptionContract>> option_contracts;
  std::optional<std::string> next_page_token;

  std::string to_json() const;
  static OptionContractsResponse from_json(const std::string& jsonStr);

  auto operator<=>(const OptionContractsResponse& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::OptionContract>
{
  using T = vp::OptionContract;
  static constexpr auto value = glz::object(
    "id", &T::id,
    "symbol", &T::symbol,
    "name", &T::name,
    "status", &T::status,
    "tradable", &T::tradable,
    "expiration_date", &T::expiration_date,
    "root_symbol", &T::root_symbol,
    "underlying_symbol", &T::underlying_symbol,
    "underlying_asset_id", &T::underlying_asset_id,
    "type", &T::type,
    "style", &T::style,
    "strike_price", &T::strike_price,
    "size", &T::size,
    "open_interest", &T::open_interest,
    "open_interest_date", &T::open_interest_date,
    "close_price", &T::close_price,
    "close_price_date", &T::close_price_date
  );
};

template <>
struct glz::meta<vp::OptionContractsResponse>
{
  using T = vp::OptionContractsResponse;
  static constexpr auto value = glz::object(
    "option_contracts", &T::option_contracts,
    "next_page_token", &T::next_page_token
  );
};

inline std::string vp::OptionContract::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::OptionContract vp::OptionContract::from_json(
  const std::string& jsonStr)
{
  vp::OptionContract obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse OptionContract JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}

inline std::string vp::OptionContractsResponse::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::OptionContractsResponse vp::OptionContractsResponse::from_json(
  const std::string& jsonStr)
{
  vp::OptionContractsResponse obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error(
      "Failed to parse OptionContractsResponse JSON: " +
      std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
