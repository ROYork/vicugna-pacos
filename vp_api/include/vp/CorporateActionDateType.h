#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the type of date for a corporate action.
 */
enum class CorporateActionDateType
{
  declaration_date, ///< "declaration_date"
  ex_date,          ///< "ex_date"
  record_date,      ///< "record_date"
  payable_date      ///< "payable_date"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::CorporateActionDateType obj);
std::string to_str(vp::CorporateActionDateType obj);
vp::CorporateActionDateType CorporateActionDateType_from_str(std::string_view str);
vp::CorporateActionDateType CorporateActionDateType_from_json(std::string_view str);
bool is_CorporateActionDateType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for CorporateActionDateType
template <>
struct glz::meta<vp::CorporateActionDateType>
{
  using enum vp::CorporateActionDateType;
  static constexpr auto value = glz::enumerate(
    declaration_date,
    ex_date,
    record_date,
    payable_date
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "declaration_date" or "ex_date" for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionDateType::declaration_date);
 *  // "declaration_date"
 *  @endcode
 */
inline std::string to_json(vp::CorporateActionDateType obj)
{
  return glz::write_json(obj).value_or("CorporateActionDateType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns declaration_date or ex_date for this enum.
 *  @code
 *  std::cout << to_json(vp::CorporateActionDateType::declaration_date);
 *  // declaration_date
 *  @endcode
 */
inline std::string to_str(vp::CorporateActionDateType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::CorporateActionDateType object.
 */
inline vp::CorporateActionDateType CorporateActionDateType_from_str(std::string_view str)
{
  vp::CorporateActionDateType s;
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
    throw std::invalid_argument("Invalid CorporateActionDateType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::CorporateActionDateType object.
 */
inline vp::CorporateActionDateType CorporateActionDateType_from_json(std::string_view str)
{
  vp::CorporateActionDateType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid CorporateActionDateType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'CorporateActionDateType'.
 */
inline bool is_CorporateActionDateType(std::string_view str)
{
  vp::CorporateActionDateType s;

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