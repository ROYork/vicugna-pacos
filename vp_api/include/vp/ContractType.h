#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the contract type of options
 */
enum class ContractType
{
  call, ///< "call"
  put   ///< "put"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::ContractType obj);
std::string to_str(vp::ContractType obj);
vp::ContractType ContractType_from_str(std::string_view str);
vp::ContractType ContractType_from_json(std::string_view str);
bool is_ContractType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for ContractType
template <>
struct glz::meta<vp::ContractType>
{
  using enum vp::ContractType;
  static constexpr auto value = glz::enumerate(
    call,
    put
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "call" or "put" for this enum.
 *  @code
 *  std::cout << to_json(vp::ContractType::call);
 *  // "call"
 *  @endcode
 */
inline std::string to_json(vp::ContractType obj)
{
  return glz::write_json(obj).value_or("ContractType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns call or put for this enum.
 *  @code
 *  std::cout << to_json(vp::ContractType::call);
 *  // call
 *  @endcode
 */
inline std::string to_str(vp::ContractType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::ContractType object.
 */
inline vp::ContractType ContractType_from_str(std::string_view str)
{
  vp::ContractType s;
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
    throw std::invalid_argument("Invalid ContractType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::ContractType object.
 */
inline vp::ContractType ContractType_from_json(std::string_view str)
{
  vp::ContractType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid ContractType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'ContractType'.
 */
inline bool is_ContractType(std::string_view str)
{
  vp::ContractType s;

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