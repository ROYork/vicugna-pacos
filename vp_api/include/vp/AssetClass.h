#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief
 * This represents the category to which the asset belongs to.
 * It serves to identify the nature of the financial instrument, with options
 * including "us_equity" for U.S. equities, "us_option" for U.S. options,
 * and "crypto" for cryptocurrencies.
 */
enum class AssetClass
{
  us_equity,
  us_option,
  crypto
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::AssetClass obj);
std::string to_str(vp::AssetClass obj);
vp::AssetClass AssetClass_from_str(std::string_view str);
vp::AssetClass AssetClass_from_json(std::string_view str);
bool is_AssetClass(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for AssetClass
template <>
struct glz::meta<vp::AssetClass>
{
  using enum vp::AssetClass;
  static constexpr auto value = glz::enumerate(
    us_equity,
    us_option,
    crypto
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "us_equity" or "us_option" for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetClass::us_equity);
 *  // "us_equity"
 *  @endcode
 */
inline std::string to_json(vp::AssetClass obj)
{
  return glz::write_json(obj).value_or("AssetClass::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns us_equity or us_option for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetClass::us_equity);
 *  // us_equity
 *  @endcode
 */
inline std::string to_str(vp::AssetClass obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::AssetClass object.
 */
inline vp::AssetClass AssetClass_from_str(std::string_view str)
{
  vp::AssetClass s;
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
    throw std::invalid_argument("Invalid AssetClass string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::AssetClass object.
 */
inline vp::AssetClass AssetClass_from_json(std::string_view str)
{
  vp::AssetClass s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid AssetClass string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'AssetClass'.
 */
inline bool is_AssetClass(std::string_view str)
{
  vp::AssetClass s;

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