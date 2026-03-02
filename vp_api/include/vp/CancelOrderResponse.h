#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <compare>
#include "vp/Order.h"

namespace vp {

/**
 * @brief Response from canceling an order
 *
 * Returned by the cancel all orders endpoint.
 * The body field is raw JSON because on 207 (multi-status) responses,
 * successful cancellations contain an Order object while failures
 * contain error objects with "code" and "message" fields.
 */
struct CancelOrderResponse
{
  int status = 0;
  std::string id = "";
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
  static CancelOrderResponse from_json(const std::string& jsonStr);

  bool operator==(const CancelOrderResponse& other) const
  {
    return status == other.status &&
           id == other.id &&
           body.str == other.body.str;
  }

  auto operator<=>(const CancelOrderResponse& other) const
  {
    if (auto cmp = status <=> other.status; cmp != 0) return cmp;
    if (auto cmp = id <=> other.id; cmp != 0) return cmp;
    return body.str <=> other.body.str;
  }
};

} // namespace vp

template <>
struct glz::meta<vp::CancelOrderResponse>
{
  using T = vp::CancelOrderResponse;
  static constexpr auto value = glz::object(
    "status", &T::status,
    "id", &T::id,
    "body", &T::body
  );
};

inline std::string vp::CancelOrderResponse::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::CancelOrderResponse vp::CancelOrderResponse::from_json(
  const std::string& jsonStr)
{
  vp::CancelOrderResponse obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error(
      "Failed to parse CancelOrderResponse JSON: " +
      std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
