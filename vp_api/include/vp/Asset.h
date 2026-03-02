#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include <compare>
#include "vp/AssetClass.h"
#include "vp/AssetExchange.h"
#include "vp/AssetStatus.h"

namespace vp {

/**
 * @brief Represents an Alpaca asset
 *
 * See https://alpaca.markets/docs/api-references/trading-api/assets/
 */
struct Asset
{
  std::string id = "";
  AssetClass asset_class = AssetClass::us_equity;
  AssetExchange exchange = AssetExchange::EMPTY;
  std::string symbol = "";
  std::string name = "";
  AssetStatus status = AssetStatus::active;
  bool tradable = false;
  bool marginable = false;
  bool shortable = false;
  bool easy_to_borrow = false;
  bool fractionable = false;
  std::optional<std::string> min_order_size;
  std::optional<std::string> min_trade_increment;
  std::optional<std::string> price_increment;
  std::optional<std::string> maintenance_margin_requirement;
  std::optional<std::vector<std::string>> attributes;

  std::string to_json() const;
  static Asset from_json(const std::string& jsonStr);

  auto operator<=>(const Asset& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::Asset>
{
  using T = vp::Asset;
  static constexpr auto value = glz::object(
    "id", &T::id,
    "class", &T::asset_class,
    "exchange", &T::exchange,
    "symbol", &T::symbol,
    "name", &T::name,
    "status", &T::status,
    "tradable", &T::tradable,
    "marginable", &T::marginable,
    "shortable", &T::shortable,
    "easy_to_borrow", &T::easy_to_borrow,
    "fractionable", &T::fractionable,
    "min_order_size", &T::min_order_size,
    "min_trade_increment", &T::min_trade_increment,
    "price_increment", &T::price_increment,
    "maintenance_margin_requirement", &T::maintenance_margin_requirement,
    "attributes", &T::attributes
  );
};

inline std::string vp::Asset::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::Asset vp::Asset::from_json(const std::string& jsonStr)
{
  vp::Asset obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse Asset JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
