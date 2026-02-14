#pragma once
#include <glaze/glaze.hpp>
#include <format>

namespace vp {

/**
 * @brief Represents the unit of time for a TimeFrame.
 */
enum class TimeFrameUnit
{
  Minute, ///< "Min"
  Hour,   ///< "Hour"
  Day,    ///< "Day"
  Week,   ///< "Week"
  Month   ///< "Month"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::TimeFrameUnit obj);
std::string to_str(vp::TimeFrameUnit obj);
vp::TimeFrameUnit TimeFrameUnit_from_str(std::string_view str);
vp::TimeFrameUnit TimeFrameUnit_from_json(std::string_view str);
bool is_TimeFrameUnit(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for TimeFrameUnit
template <>
struct glz::meta<vp::TimeFrameUnit>
{
  using enum vp::TimeFrameUnit;
  static constexpr auto value = glz::enumerate(
    Minute,
    Hour,
    Day,
    Week,
    Month
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "Min" or "Hour" for this enum.
 *  @code
 *  std::cout << to_json(vp::TimeFrameUnit::Minute);
 *  // "Min"
 *  @endcode
 */
inline std::string to_json(vp::TimeFrameUnit obj)
{
  return std::format("\"{}\"", to_str(obj));
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns Min or Hour for this enum.
 *  @code
 *  std::cout << to_json(vp::TimeFrameUnit::Minute);
 *  // Min
 *  @endcode
 */
inline std::string to_str(vp::TimeFrameUnit obj)
{
  switch (obj) {
    case vp::TimeFrameUnit::Minute: return "Min";
    case vp::TimeFrameUnit::Hour: return "Hour";
    case vp::TimeFrameUnit::Day: return "Day";
    case vp::TimeFrameUnit::Week: return "Week";
    case vp::TimeFrameUnit::Month: return "Month";
  }
  return "TimeFrameUnit::to_str::error";
}

/**
 * @brief Convert a string_view to a vp::TimeFrameUnit object.
 */
inline vp::TimeFrameUnit TimeFrameUnit_from_str(std::string_view str)
{
  if (str == "Min") return vp::TimeFrameUnit::Minute;
  if (str == "Hour") return vp::TimeFrameUnit::Hour;
  if (str == "Day") return vp::TimeFrameUnit::Day;
  if (str == "Week") return vp::TimeFrameUnit::Week;
  if (str == "Month") return vp::TimeFrameUnit::Month;
  throw std::invalid_argument("Invalid TimeFrameUnit string: " + std::string(str));
}

/**
 * @brief Convert a string_view to a vp::TimeFrameUnit object.
 */
inline vp::TimeFrameUnit TimeFrameUnit_from_json(std::string_view str)
{
  if (str == "Min") return vp::TimeFrameUnit::Minute;
  if (str == "Hour") return vp::TimeFrameUnit::Hour;
  if (str == "Day") return vp::TimeFrameUnit::Day;
  if (str == "Week") return vp::TimeFrameUnit::Week;
  if (str == "Month") return vp::TimeFrameUnit::Month;
  throw std::invalid_argument("Invalid TimeFrameUnit string: " + std::string(str));
}

/**
 * @brief Returns true if the string_view is a valid 'TimeFrameUnit'.
 */
inline bool is_TimeFrameUnit(std::string_view str)
{
  return str == "Min" || str == "Min" ||
         str == "Hour" || str == "Hour" ||
         str == "Day" || str == "Day" ||
         str == "Week" || str == "Week" ||
         str == "Month" || str == "Month";
}
