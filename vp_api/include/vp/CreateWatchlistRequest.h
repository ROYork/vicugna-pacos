#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <vector>

namespace vp {

/**
 * @brief Request parameters for creating a watchlist
 */
struct CreateWatchlistRequest
{
  std::string name = "";
  std::vector<std::string> symbols;

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
struct glz::meta<vp::CreateWatchlistRequest>
{
  using T = vp::CreateWatchlistRequest;
  static constexpr auto value = glz::object(
    "name", &T::name,
    "symbols", &T::symbols
  );
};
