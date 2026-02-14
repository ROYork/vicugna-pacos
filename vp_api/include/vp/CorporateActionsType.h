#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The type of corporate action.
 * ref. https://docs.alpaca.markets/reference/corporateactions-1
 */
enum class CorporateActionsType
{
  reverse_split,        ///< "reverse_split"
  forward_split,        ///< "forward_split"
  unit_split,           ///< "unit_split"
  cash_dividend,        ///< "cash_dividend"
  stock_dividend,       ///< "stock_dividend"
  spin_off,             ///< "spin_off"
  cash_merger,          ///< "cash_merger"
  stock_merger,         ///< "stock_merger"
  stock_and_cash_merger,///< "stock_and_cash_merger"
  redemption,           ///< "redemption"
  name_change,          ///< "name_change"
  worthless_removal,    ///< "worthless_removal"
  rights_distribution   ///< "rights_distribution"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::CorporateActionsType obj);
std::string to_str(vp::CorporateActionsType obj);
vp::CorporateActionsType CorporateActionsType_from_str(std::string_view str);
vp::CorporateActionsType CorporateActionsType_from_json(std::string_view str);
bool is_CorporateActionsType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for CorporateActionsType
template <>
struct glz::meta<vp::CorporateActionsType>
{
  using enum vp::CorporateActionsType;
  static constexpr auto value = glz::enumerate(
    reverse_split,
    forward_split,
    unit_split,
    cash_dividend,
    stock_dividend,
    spin_off,
    cash_merger,
    stock_merger,
    stock_and_cash_merger,
    redemption,
    name_change,
    worthless_removal,
    rights_distribution
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "reverse_split" or "forward_split" for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionsType::reverse_split);
 *  // "reverse_split"
 *  @endcode
 */
inline std::string to_json(vp::CorporateActionsType obj)
{
  return glz::write_json(obj).value_or("CorporateActionsType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns reverse_split or forward_split for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionsType::reverse_split);
 *  // reverse_split
 *  @endcode
 */
inline std::string to_str(vp::CorporateActionsType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::CorporateActionsType object.
 */
inline vp::CorporateActionsType CorporateActionsType_from_str(std::string_view str)
{
  vp::CorporateActionsType s;
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
    throw std::invalid_argument("Invalid CorporateActionsType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::CorporateActionsType object.
 */
inline vp::CorporateActionsType CorporateActionsType_from_json(std::string_view str)
{
  vp::CorporateActionsType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid CorporateActionsType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'CorporateActionsType'.
 */
inline bool is_CorporateActionsType(std::string_view str)
{
  vp::CorporateActionsType s;

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
