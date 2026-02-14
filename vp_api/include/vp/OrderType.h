#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what type of order this is.
 *
 * The order types supported by Alpaca vary based on the order's security type.
 * The following provides a comprehensive breakdown of the supported order types for each category:
 * - Equity trading: market, limit, stop, stop_limit, trailing_stop.
 * - Options trading: market, limit, stop, stop_limit.
 * - Crypto trading: market, limit, stop_limit.
 */
enum class OrderType
{
  market,       ///< "market"
  limit,        ///< "limit"
  stop,         ///< "stop"
  stop_limit,   ///< "stop_limit"
  trailing_stop ///< "trailing_stop"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::OrderType obj);
std::string to_str(vp::OrderType obj);
vp::OrderType OrderType_from_str(std::string_view str);
vp::OrderType OrderType_from_json(std::string_view str);
bool is_OrderType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for OrderType
template <>
struct glz::meta<vp::OrderType>
{
  using enum vp::OrderType;
  static constexpr auto value = glz::enumerate(
    market,
    limit,
    stop,
    stop_limit,
    trailing_stop
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "market" or "limit" for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderType::market);
 *  // "market"
 *  @endcode
 */
inline std::string to_json(vp::OrderType obj)
{
  return glz::write_json(obj).value_or("OrderType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns market or limit for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderType::market);
 *  // market
 *  @endcode
 */
inline std::string to_str(vp::OrderType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::OrderType object.
 */
inline vp::OrderType OrderType_from_str(std::string_view str)
{
  vp::OrderType s;
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
    throw std::invalid_argument("Invalid OrderType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::OrderType object.
 */
inline vp::OrderType OrderType_from_json(std::string_view str)
{
  vp::OrderType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid OrderType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'OrderType'.
 */
inline bool is_OrderType(std::string_view str)
{
  vp::OrderType s;

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