#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <compare>
#include "vp/Order.h"

namespace vp {

/**
 * @brief Response from closing a position via close_all_positions
 *
 * The body field is raw JSON because on 207 (multi-status) responses,
 * successful closures contain an Order object while failures
 * contain error objects with "code" and "message" fields.
 */
struct ClosePositionResponse
{
  std::string symbol = "";
  int status = 0;
  glz::raw_json body = {};

  /// Attempt to parse body as an Order. Returns nullopt if body
  /// does not represent a valid Order (e.g., error responses).
  std::optional<Order> get_order() const
  {
    Order order;
    auto ec = glz::read_json(order, body.str);
    if (ec)
    {
      return std::nullopt;
    }
    return order;
  }

  std::string to_json() const;
  static ClosePositionResponse from_json(const std::string& jsonStr);

  bool operator==(const ClosePositionResponse& other) const
  {
    return symbol == other.symbol &&
           status == other.status &&
           body.str == other.body.str;
  }

  auto operator<=>(const ClosePositionResponse& other) const
  {
    if (auto cmp = symbol <=> other.symbol; cmp != 0) return cmp;
    if (auto cmp = status <=> other.status; cmp != 0) return cmp;
    return body.str <=> other.body.str;
  }
};

} // namespace vp

template <>
struct glz::meta<vp::ClosePositionResponse>
{
  using T = vp::ClosePositionResponse;
  static constexpr auto value = glz::object(
    "symbol", &T::symbol,
    "status", &T::status,
    "body", &T::body
  );
};

inline std::string vp::ClosePositionResponse::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::ClosePositionResponse vp::ClosePositionResponse::from_json(
  const std::string& jsonStr)
{
  vp::ClosePositionResponse obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error(
      "Failed to parse ClosePositionResponse JSON: " +
      std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
