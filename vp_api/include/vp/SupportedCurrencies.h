#pragma once
#include <glaze/glaze.hpp>

// From Common Module

namespace vp {

/**
 * @brief  The various currencies that can be supported for LCT.
 *
 *  see https://alpaca.markets/support/local-currency-trading-faq
 */
enum class SupportedCurrencies
{
  USD,
  GBP,
  CHF,
  EUR,
  CAD,
  JPY,
  TRY,
  AUD,
  CZK,
  SEK,
  DKK,
  SGD,
  HKD,
  HUF,
  NZD,
  NOK,
  PLN
};




} // End alpaca namespace



// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::SupportedCurrencies obj);
std::string to_str(vp::SupportedCurrencies obj);
vp::SupportedCurrencies SupportedCurrencies_from_str(std::string_view str);
vp::SupportedCurrencies SupportedCurrencies_from_json(std::string_view str);
bool is_SupportedCurrencies(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for SupportedCurrencies
template <>
struct glz::meta<vp::SupportedCurrencies>
{
  using enum vp::SupportedCurrencies;
  static constexpr auto value = glz::enumerate(
    USD,
    GBP,
    CHF,
    EUR,
    CAD,
    JPY,
    TRY,
    AUD,
    CZK,
    SEK,
    DKK,
    SGD,
    HKD,
    HUF,
    NZD,
    NOK,
    PLN
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "USD" or "GBP" for this enum.
 *  @code
 *  std::cout << to_json(vp::SupportedCurrencies::USD);
 *  // "USD"
 *  @endcode
 */
inline std::string to_json(vp::SupportedCurrencies obj)
{
  return glz::write_json(obj).value_or("SupportedCurrencies::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns USD or GBP for this enum.
 *  @code
 *  std::cout << to_json(vp::SupportedCurrencies::USD);
 *  // USD
 *  @endcode
 */
inline std::string to_str(vp::SupportedCurrencies obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::SupportedCurrencies object.
 */
inline vp::SupportedCurrencies SupportedCurrencies_from_str(std::string_view str)
{
  vp::SupportedCurrencies s;
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
    throw std::invalid_argument("Invalid SupportedCurrencies string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::SupportedCurrencies object.
 */
inline vp::SupportedCurrencies SupportedCurrencies_from_json(std::string_view str)
{
  vp::SupportedCurrencies s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid SupportedCurrencies string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'SupportedCurrencies'.
 */
inline bool is_SupportedCurrencies(std::string_view str)
{
  vp::SupportedCurrencies s;

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








