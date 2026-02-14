#pragma once
#include <glaze/glaze.hpp>

// From Common Module

namespace vp {

/**
 * @brief Represents the type of TradeActivity.
 *
 * Please see https://alpaca.markets/docs/api-references/broker-api/accounts/account-activities/#attributes
 */
enum class TradeActivityType
{
  partial_fill,
  fill
};

} // End alpaca namespace

// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::TradeActivityType obj);
std::string to_str(vp::TradeActivityType obj);
vp::TradeActivityType TradeActivityType_from_str(std::string_view str);
vp::TradeActivityType TradeActivityType_from_json(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for TradeActivityType
template <>
struct glz::meta<vp::TradeActivityType>
{
  using enum vp::TradeActivityType;
  static constexpr auto value = glz::enumerate(
    partial_fill,
    fill
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "partial_fill" or "fill" for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeActivityType::fill);
 *  // "fill"
 *  @endcode
 */
inline std::string to_json(vp::TradeActivityType obj)
{
  return glz::write_json(obj).value_or("\"TradeActivityType::to_json::error\"");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns partial_fill or fill for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeActivityType::fill);
 *  // fill
 *  @endcode
 */
inline std::string to_str(vp::TradeActivityType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::TradeActivityType object.
 */
inline vp::TradeActivityType TradeActivityType_from_str(std::string_view str)
{
  vp::TradeActivityType s;
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
    throw std::invalid_argument("Invalid TradeActivityType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::TradeActivityType object.
 */
inline vp::TradeActivityType TradeActivityType_from_json(std::string_view str)
{
  vp::TradeActivityType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid TradeActivityType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'TradeActivityType'.
 */
bool is_TradeActivityType(std::string_view str)
{
  vp::TradeActivityType s;

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
