#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The specific types of corporate actions. Each subtype is related to CorporateActionType.
 *
 * Learn more here: https://alpaca.markets/docs/api-references/trading-api/corporate-actions-announcements/
 */
enum class CorporateActionSubType
{
  cash,             ///< "cash"
  stock,            ///< "stock"
  merger_update,    ///< "merger_update"
  merger_completion,///< "merger_completion"
  spinoff,          ///< "spinoff"
  stock_split,      ///< "stock_split"
  unit_split,       ///< "unit_split"
  reverse_split,    ///< "reverse_split"
  recapitalization  ///< "recapitalization"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::CorporateActionSubType obj);
std::string to_str(vp::CorporateActionSubType obj);
vp::CorporateActionSubType CorporateActionSubType_from_str(std::string_view str);
vp::CorporateActionSubType CorporateActionSubType_from_json(std::string_view str);
bool is_CorporateActionSubType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for CorporateActionSubType
template <>
struct glz::meta<vp::CorporateActionSubType>
{
  using enum vp::CorporateActionSubType;
  static constexpr auto value = glz::enumerate(
    cash,
    stock,
    merger_update,
    merger_completion,
    spinoff,
    stock_split,
    unit_split,
    reverse_split,
    recapitalization
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "cash" or "stock" for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionSubType::cash);
 *  // "cash"
 *  @endcode
 */
inline std::string to_json(vp::CorporateActionSubType obj)
{
  return glz::write_json(obj).value_or("CorporateActionSubType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns cash or stock for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionSubType::cash);
 *  // cash
 *  @endcode
 */
inline std::string to_str(vp::CorporateActionSubType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::CorporateActionSubType object.
 */
inline vp::CorporateActionSubType CorporateActionSubType_from_str(std::string_view str)
{
  vp::CorporateActionSubType s;
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
    throw std::invalid_argument("Invalid CorporateActionSubType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::CorporateActionSubType object.
 */
inline vp::CorporateActionSubType CorporateActionSubType_from_json(std::string_view str)
{
  vp::CorporateActionSubType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid CorporateActionSubType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'CorporateActionSubType'.
 */
inline bool is_CorporateActionSubType(std::string_view str)
{
  vp::CorporateActionSubType s;

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