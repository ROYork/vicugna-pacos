#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>

namespace vp {

/**
 * @brief Request parameters for updating a watchlist
 */
struct UpdateWatchlistRequest
{
  std::optional<std::string> name;
  std::optional<std::vector<std::string>> symbols;

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
struct glz::meta<vp::UpdateWatchlistRequest>
{
  using T = vp::UpdateWatchlistRequest;
  static constexpr auto value = glz::object(
    "name", &T::name,
    "symbols", &T::symbols
  );
};
