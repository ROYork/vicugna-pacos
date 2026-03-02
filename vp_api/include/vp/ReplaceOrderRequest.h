#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include "vp/TimeInForce.h"

namespace vp {

/**
 * @brief Request parameters for replacing an existing order
 */
struct ReplaceOrderRequest
{
  std::optional<std::string> qty;
  std::optional<TimeInForce> time_in_force;
  std::optional<double> limit_price;
  std::optional<double> stop_price;
  std::optional<double> trail;
  std::optional<std::string> client_order_id;

  std::string to_json() const
  {
    std::string json_string{};
    auto error = glz::write_json(*this, json_string);
    if (error)
    {
      return "{}";
    }
    return json_string;
  }
};

} // namespace vp

template <>
struct glz::meta<vp::ReplaceOrderRequest>
{
  using T = vp::ReplaceOrderRequest;
  static constexpr auto value = glz::object(
    "qty", &T::qty,
    "time_in_force", &T::time_in_force,
    "limit_price", &T::limit_price,
    "stop_price", &T::stop_price,
    "trail", &T::trail,
    "client_order_id", &T::client_order_id
  );
};
