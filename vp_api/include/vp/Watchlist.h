#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include <compare>
#include "vp/Asset.h"

namespace vp {

/**
 * @brief Represents an Alpaca watchlist
 *
 * See https://alpaca.markets/docs/api-references/trading-api/watchlist/
 */
struct Watchlist
{
  std::string id = "";
  std::string account_id = "";
  std::string name = "";
  std::string created_at = "";
  std::string updated_at = "";
  std::optional<std::vector<Asset>> assets;

  std::string to_json() const;
  static Watchlist from_json(const std::string& jsonStr);

  auto operator<=>(const Watchlist& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::Watchlist>
{
  using T = vp::Watchlist;
  static constexpr auto value = glz::object(
    "id", &T::id,
    "account_id", &T::account_id,
    "name", &T::name,
    "created_at", &T::created_at,
    "updated_at", &T::updated_at,
    "assets", &T::assets
  );
};

inline std::string vp::Watchlist::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::Watchlist vp::Watchlist::from_json(const std::string& jsonStr)
{
  vp::Watchlist obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse Watchlist JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
