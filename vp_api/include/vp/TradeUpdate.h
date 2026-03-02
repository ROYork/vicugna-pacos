#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <compare>
#include "vp/TradeEvent.h"
#include "vp/Order.h"

namespace vp {

/**
 * @brief Represents a trade update from WebSocket stream
 *
 * See https://alpaca.markets/docs/api-references/trading-api/streaming/
 */
struct TradeUpdate
{
  TradeEvent event = TradeEvent::new_;
  std::optional<std::string> execution_id;
  Order order = {};
  std::optional<std::string> timestamp;
  std::optional<std::string> position_qty;
  std::optional<std::string> price;
  std::optional<std::string> qty;

  std::string to_json() const;
  static TradeUpdate from_json(const std::string& jsonStr);

  auto operator<=>(const TradeUpdate& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::TradeUpdate>
{
  using T = vp::TradeUpdate;
  static constexpr auto value = glz::object(
    "event", &T::event,
    "execution_id", &T::execution_id,
    "order", &T::order,
    "timestamp", &T::timestamp,
    "position_qty", &T::position_qty,
    "price", &T::price,
    "qty", &T::qty
  );
};

inline std::string vp::TradeUpdate::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::TradeUpdate vp::TradeUpdate::from_json(
  const std::string& jsonStr)
{
  vp::TradeUpdate obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse TradeUpdate JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
