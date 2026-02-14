#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Data normalization based on types of corporate actions.
 */
enum class Adjustment
{
  raw,     ///< "raw"
  split,   ///< "split"
  dividend,///< "dividend"
  all      ///< "all"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::Adjustment obj);
std::string to_str(vp::Adjustment obj);
vp::Adjustment Adjustment_from_str(std::string_view str);
vp::Adjustment Adjustment_from_json(std::string_view str);
bool is_Adjustment(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for Adjustment
template <>
struct glz::meta<vp::Adjustment>
{
  using enum vp::Adjustment;
  static constexpr auto value = glz::enumerate(
    raw,
    split,
    dividend,
    all
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "raw" or "split" for this enum.
 *  @code
 *  std::cout << to_json(vp::Adjustment::raw);
 *  // "raw"
 *  @endcode
 */
inline std::string to_json(vp::Adjustment obj)
{
  return glz::write_json(obj).value_or("Adjustment::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns raw or split for this enum.
 *  @code
 *  std::cout << to_json(vp::Adjustment::raw);
 *  // raw
 *  @endcode
 */
inline std::string to_str(vp::Adjustment obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::Adjustment object.
 */
inline vp::Adjustment Adjustment_from_str(std::string_view str)
{
  vp::Adjustment s;
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
    throw std::invalid_argument("Invalid Adjustment string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::Adjustment object.
 */
inline vp::Adjustment Adjustment_from_json(std::string_view str)
{
  vp::Adjustment s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid Adjustment string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'Adjustment'.
 */
inline bool is_Adjustment(std::string_view str)
{
  vp::Adjustment s;

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
