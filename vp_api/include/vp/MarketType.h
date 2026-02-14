#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Market types.
 */
enum class MarketType
{
  stocks, ///< "stocks"
  crypto  ///< "crypto"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::MarketType obj);
std::string to_str(vp::MarketType obj);
vp::MarketType MarketType_from_str(std::string_view str);
vp::MarketType MarketType_from_json(std::string_view str);
bool is_MarketType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for MarketType
template <>
struct glz::meta<vp::MarketType>
{
  using enum vp::MarketType;
  static constexpr auto value = glz::enumerate(
    stocks,
    crypto
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "stocks" or "crypto" for this enum.
 *  @code
 *  std::cout << to_json(vp::MarketType::stocks);
 *  // "stocks"
 *  @endcode
 */
inline std::string to_json(vp::MarketType obj)
{
  return glz::write_json(obj).value_or("MarketType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns stocks or crypto for this enum.
 *  @code
 *  std::cout << to_json(vp::MarketType::stocks);
 *  // stocks
 *  @endcode
 */
inline std::string to_str(vp::MarketType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::MarketType object.
 */
inline vp::MarketType MarketType_from_str(std::string_view str)
{
  vp::MarketType s;
  const std::string json = "\"" + std::string(str) + "\"";
  auto error = glz::read_json(s, json);
  if (error)
  {
    // Check to see if the user passed a json type wrapped in quotes.
    auto error2 = glz::read_json(s, str);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid MarketType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::MarketType object.
 */
inline vp::MarketType MarketType_from_json(std::string_view str)
{
  vp::MarketType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid MarketType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'MarketType'.
 */
inline bool is_MarketType(std::string_view str)
{
  vp::MarketType s;

  auto error = glz::read_json(s, str);
  if(!error)
  {
    return true;
  }
  else
  {
    std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return true;
    }
  }
  return false;
}
