#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Specifies when to run a PDT check for an account.
 *
 * NOTE: These values are currently the same as DTBPCheck however they are not guaranteed to be in sync the future
 *
 * please see https://alpaca.markets/docs/api-references/broker-api/trading/trading-configurations/#attributes
 * for more info.
 */
enum class PDTCheck
{
  both,  ///< "both"
  entry, ///< "entry"
  exit   ///< "exit"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::PDTCheck obj);
std::string to_str(vp::PDTCheck obj);
vp::PDTCheck PDTCheck_from_str(std::string_view str);
vp::PDTCheck PDTCheck_from_json(std::string_view str);
bool is_PDTCheck(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for PDTCheck
template <>
struct glz::meta<vp::PDTCheck>
{
  using enum vp::PDTCheck;
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
 *  std::cout << to_json(vp::PDTCheck::both);
 *  // "both"
 *  @endcode
 */
inline std::string to_json(vp::PDTCheck obj)
{
  return glz::write_json(obj).value_or("PDTCheck::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns both or entry for this enum.
 *  @code
 *  std::cout << to_json(vp::PDTCheck::both);
 *  // both
 *  @endcode
 */
inline std::string to_str(vp::PDTCheck obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::PDTCheck object.
 */
inline vp::PDTCheck PDTCheck_from_str(std::string_view str)
{
  vp::PDTCheck s;
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
    throw std::invalid_argument("Invalid PDTCheck string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::PDTCheck object.
 */
inline vp::PDTCheck PDTCheck_from_json(std::string_view str)
{
  vp::PDTCheck s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid PDTCheck string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'PDTCheck'.
 */
inline bool is_PDTCheck(std::string_view str)
{
  vp::PDTCheck s;

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