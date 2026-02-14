#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the category of an Activity
 */
enum class ActivityCategory
{
  trade_activity,     ///< "trade_activity"
  non_trade_activity  ///< "non_trade_activity"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::ActivityCategory obj);
std::string to_str(vp::ActivityCategory obj);
vp::ActivityCategory ActivityCategory_from_str(std::string_view str);
vp::ActivityCategory ActivityCategory_from_json(std::string_view str);
bool is_ActivityCategory(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for ActivityCategory
template <>
struct glz::meta<vp::ActivityCategory>
{
  using enum vp::ActivityCategory;
  static constexpr auto value = glz::enumerate(
    trade_activity,
    non_trade_activity
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "trade_activity" or "non_trade_activity" for this enum.
 *  @code
 *  std::cout << to_json(vp::ActivityCategory::trade_activity);
 *  // "trade_activity"
 *  @endcode
 */
inline std::string to_json(vp::ActivityCategory obj)
{
  return glz::write_json(obj).value_or("ActivityCategory::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns trade_activity or non_trade_activity for this enum.
 *  @code
 *  std::cout << to_json(vp::ActivityCategory::trade_activity);
 *  // trade_activity
 *  @endcode
 */
inline std::string to_str(vp::ActivityCategory obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::ActivityCategory object.
 */
inline vp::ActivityCategory ActivityCategory_from_str(std::string_view str)
{
  vp::ActivityCategory s;
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
    throw std::invalid_argument("Invalid ActivityCategory string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::ActivityCategory object.
 */
inline vp::ActivityCategory ActivityCategory_from_json(std::string_view str)
{
  vp::ActivityCategory s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid ActivityCategory string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'ActivityCategory'.
 */
inline bool is_ActivityCategory(std::string_view str)
{
  vp::ActivityCategory s;

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