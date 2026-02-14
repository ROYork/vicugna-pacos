#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the various states for an Asset's lifecycle
 */
enum class AssetStatus
{
  active,   ///< "active"
  inactive  ///< "inactive"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::AssetStatus obj);
std::string to_str(vp::AssetStatus obj);
vp::AssetStatus AssetStatus_from_str(std::string_view str);
vp::AssetStatus AssetStatus_from_json(std::string_view str);
bool is_AssetStatus(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for AssetStatus
template <>
struct glz::meta<vp::AssetStatus>
{
  using enum vp::AssetStatus;
  static constexpr auto value = glz::enumerate(
    active,
    inactive
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "active" or "inactive" for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetStatus::active);
 *  // "active"
 *  @endcode
 */
inline std::string to_json(vp::AssetStatus obj)
{
  return glz::write_json(obj).value_or("AssetStatus::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns active or inactive for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetStatus::active);
 *  // active
 *  @endcode
 */
inline std::string to_str(vp::AssetStatus obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::AssetStatus object.
 */
inline vp::AssetStatus AssetStatus_from_str(std::string_view str)
{
  vp::AssetStatus s;
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
    throw std::invalid_argument("Invalid AssetStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::AssetStatus object.
 */
inline vp::AssetStatus AssetStatus_from_json(std::string_view str)
{
  vp::AssetStatus s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid AssetStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'AssetStatus'.
 */
inline bool is_AssetStatus(std::string_view str)
{
  vp::AssetStatus s;

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