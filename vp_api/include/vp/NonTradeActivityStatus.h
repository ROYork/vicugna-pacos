#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the status of a NonTradeActivity.
 *
 * Please see https://alpaca.markets/docs/api-references/broker-api/accounts/account-activities/#enumaccountactivity
 * for more info.
 */
enum class NonTradeActivityStatus
{
  executed, ///< "executed"
  correct,  ///< "correct"
  canceled  ///< "canceled"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::NonTradeActivityStatus obj);
std::string to_str(vp::NonTradeActivityStatus obj);
vp::NonTradeActivityStatus NonTradeActivityStatus_from_str(std::string_view str);
vp::NonTradeActivityStatus NonTradeActivityStatus_from_json(std::string_view str);
bool is_NonTradeActivityStatus(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for NonTradeActivityStatus
template <>
struct glz::meta<vp::NonTradeActivityStatus>
{
  using enum vp::NonTradeActivityStatus;
  static constexpr auto value = glz::enumerate(
    executed,
    correct,
    canceled
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "executed" or "correct" for this enum.
 *  @code
 *  std::cout << to_json(vp::NonTradeActivityStatus::executed);
 *  // "executed"
 *  @endcode
 */
inline std::string to_json(vp::NonTradeActivityStatus obj)
{
  return glz::write_json(obj).value_or("NonTradeActivityStatus::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns executed or correct for this enum.
 *  @code
 *  std::cout << to_json(vp::NonTradeActivityStatus::executed);
 *  // executed
 *  @endcode
 */
inline std::string to_str(vp::NonTradeActivityStatus obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::NonTradeActivityStatus object.
 */
inline vp::NonTradeActivityStatus NonTradeActivityStatus_from_str(std::string_view str)
{
  vp::NonTradeActivityStatus s;
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
    throw std::invalid_argument("Invalid NonTradeActivityStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::NonTradeActivityStatus object.
 */
inline vp::NonTradeActivityStatus NonTradeActivityStatus_from_json(std::string_view str)
{
  vp::NonTradeActivityStatus s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid NonTradeActivityStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'NonTradeActivityStatus'.
 */
inline bool is_NonTradeActivityStatus(std::string_view str)
{
  vp::NonTradeActivityStatus s;

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