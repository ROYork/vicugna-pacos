#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Used for controlling when an Account will receive a trade confirmation email.
 *
 * please see https://docs.alpaca.markets/reference/getaccountconfig
 * for more info.
 */
enum class TradeConfirmationEmail
{
  all,  ///< "all"
  none  ///< "none"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::TradeConfirmationEmail obj);
std::string to_str(vp::TradeConfirmationEmail obj);
vp::TradeConfirmationEmail TradeConfirmationEmail_from_str(std::string_view str);
vp::TradeConfirmationEmail TradeConfirmationEmail_from_json(std::string_view str);
bool is_TradeConfirmationEmail(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for TradeConfirmationEmail
template <>
struct glz::meta<vp::TradeConfirmationEmail>
{
  using enum vp::TradeConfirmationEmail;
  static constexpr auto value = glz::enumerate(
    all,
    none
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "all" or "none" for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeConfirmationEmail::all);
 *  // "all"
 *  @endcode
 */
inline std::string to_json(vp::TradeConfirmationEmail obj)
{
  return glz::write_json(obj).value_or("TradeConfirmationEmail::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns all or none for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeConfirmationEmail::all);
 *  // all
 *  @endcode
 */
inline std::string to_str(vp::TradeConfirmationEmail obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::TradeConfirmationEmail object.
 */
inline vp::TradeConfirmationEmail TradeConfirmationEmail_from_str(std::string_view str)
{
  vp::TradeConfirmationEmail s;
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
    throw std::invalid_argument("Invalid TradeConfirmationEmail string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::TradeConfirmationEmail object.
 */
inline vp::TradeConfirmationEmail TradeConfirmationEmail_from_json(std::string_view str)
{
  vp::TradeConfirmationEmail s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid TradeConfirmationEmail string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'TradeConfirmationEmail'.
 */
inline bool is_TradeConfirmationEmail(std::string_view str)
{
  vp::TradeConfirmationEmail s;

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