#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what class of order this is.
 *
 * The order classes supported by Alpaca vary based on the order's security type.
 * The following provides a comprehensive breakdown of the supported order classes for each category:
 * - Equity trading: simple (or ""), oco, oto, bracket.
 * - Options trading: simple (or ""), mleg (required for multi-leg complex options strategies).
 * - Crypto trading: simple (or "").
 */
enum class OrderClass
{
  simple,  ///< "simple"
  mleg,    ///< "mleg"
  bracket, ///< "bracket"
  oco,     ///< "oco"
  oto      ///< "oto"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::OrderClass obj);
std::string to_str(vp::OrderClass obj);
vp::OrderClass OrderClass_from_str(std::string_view str);
vp::OrderClass OrderClass_from_json(std::string_view str);
bool is_OrderClass(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for OrderClass
template <>
struct glz::meta<vp::OrderClass>
{
  using enum vp::OrderClass;
  static constexpr auto value = glz::enumerate(
    simple,
    mleg,
    bracket,
    oco,
    oto
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "simple" or "mleg" for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderClass::simple);
 *  // "simple"
 *  @endcode
 */
inline std::string to_json(vp::OrderClass obj)
{
  return glz::write_json(obj).value_or("OrderClass::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns simple or mleg for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderClass::simple);
 *  // simple
 *  @endcode
 */
inline std::string to_str(vp::OrderClass obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::OrderClass object.
 */
inline vp::OrderClass OrderClass_from_str(std::string_view str)
{
  vp::OrderClass s;
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
    throw std::invalid_argument("Invalid OrderClass string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::OrderClass object.
 */
inline vp::OrderClass OrderClass_from_json(std::string_view str)
{
  vp::OrderClass s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid OrderClass string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'OrderClass'.
 */
inline bool is_OrderClass(std::string_view str)
{
  vp::OrderClass s;

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