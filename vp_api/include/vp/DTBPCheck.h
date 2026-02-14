#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Specifies when to run a DTBP check for an account.
 *
 * NOTE: These values are currently the same as PDTCheck however they are not guaranteed to be in sync the future
 *
 * please see https://alpaca.markets/docs/api-references/broker-api/trading/trading-configurations/#attributes
 * for more info.
 */
enum class DTBPCheck
{
  both,  ///< "both"
  entry, ///< "entry"
  exit   ///< "exit"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::DTBPCheck obj);
std::string to_str(vp::DTBPCheck obj);
vp::DTBPCheck DTBPCheck_from_str(std::string_view str);
vp::DTBPCheck DTBPCheck_from_json(std::string_view str);
bool is_DTBPCheck(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for DTBPCheck
template <>
struct glz::meta<vp::DTBPCheck>
{
  using enum vp::DTBPCheck;
  static constexpr auto value = glz::enumerate(
    both,
    entry,
    exit
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "both" or "entry" for this enum.
 *  @code
 *  std::cout << to_json(vp::DTBPCheck::both);
 *  // "both"
 *  @endcode
 */
inline std::string to_json(vp::DTBPCheck obj)
{
  return glz::write_json(obj).value_or("DTBPCheck::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns both or entry for this enum.
 *  @code
 *  std::cout << to_json(vp::DTBPCheck::both);
 *  // both
 *  @endcode
 */
inline std::string to_str(vp::DTBPCheck obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::DTBPCheck object.
 */
inline vp::DTBPCheck DTBPCheck_from_str(std::string_view str)
{
  vp::DTBPCheck s;
  const std::string json = std::string("\"") + std::string(str) + std::string("\"");
  auto error = glz::read_json(s, json);
  if (error)
  {
    // Check to see if the user passed a json type wrapped in quotes.
    auto error2 = glz::read_json(s, str);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid DTBPCheck string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::DTBPCheck object.
 */
inline vp::DTBPCheck DTBPCheck_from_json(std::string_view str)
{
  vp::DTBPCheck s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid DTBPCheck string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'DTBPCheck'.
 */
inline bool is_DTBPCheck(std::string_view str)
{
  vp::DTBPCheck s;

  auto error = glz::read_json(s, str);
  if(!error)
  {
    return true;
  }
  else
  {
    std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return true;
    }
  }
  return false;
}