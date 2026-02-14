#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The general types of corporate action events.
 *
 * Learn more here: https://alpaca.markets/docs/api-references/trading-api/corporate-actions-announcements/
 */
enum class CorporateActionType
{
  dividend, ///< "dividend"
  merger,   ///< "merger"
  spinoff,  ///< "spinoff"
  split     ///< "split"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::CorporateActionType obj);
std::string to_str(vp::CorporateActionType obj);
vp::CorporateActionType CorporateActionType_from_str(std::string_view str);
vp::CorporateActionType CorporateActionType_from_json(std::string_view str);
bool is_CorporateActionType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for CorporateActionType
template <>
struct glz::meta<vp::CorporateActionType>
{
  using enum vp::CorporateActionType;
  static constexpr auto value = glz::enumerate(
    dividend,
    merger,
    spinoff,
    split
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "dividend" or "merger" for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionType::dividend);
 *  // "dividend"
 *  @endcode
 */
inline std::string to_json(vp::CorporateActionType obj)
{
  return glz::write_json(obj).value_or("CorporateActionType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns dividend or merger for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionType::dividend);
 *  // dividend
 *  @endcode
 */
inline std::string to_str(vp::CorporateActionType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::CorporateActionType object.
 */
inline vp::CorporateActionType CorporateActionType_from_str(std::string_view str)
{
  vp::CorporateActionType s;
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
    throw std::invalid_argument("Invalid CorporateActionType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::CorporateActionType object.
 */
inline vp::CorporateActionType CorporateActionType_from_json(std::string_view str)
{
  vp::CorporateActionType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid CorporateActionType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'CorporateActionType'.
 */
inline bool is_CorporateActionType(std::string_view str)
{
  vp::CorporateActionType s;

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