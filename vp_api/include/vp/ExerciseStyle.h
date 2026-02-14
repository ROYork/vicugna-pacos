#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the exercise style of options
 */
enum class ExerciseStyle
{
  american, ///< "american"
  european  ///< "european"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::ExerciseStyle obj);
std::string to_str(vp::ExerciseStyle obj);
vp::ExerciseStyle ExerciseStyle_from_str(std::string_view str);
vp::ExerciseStyle ExerciseStyle_from_json(std::string_view str);
bool is_ExerciseStyle(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for ExerciseStyle
template <>
struct glz::meta<vp::ExerciseStyle>
{
  using enum vp::ExerciseStyle;
  static constexpr auto value = glz::enumerate(
    american,
    european
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "american" or "european" for this enum.
 *  @code
 *  std::cout << to_json(vp::ExerciseStyle::american);
 *  // "american"
 *  @endcode
 */
inline std::string to_json(vp::ExerciseStyle obj)
{
  return glz::write_json(obj).value_or("ExerciseStyle::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns american or european for this enum.
 *  @code
 *  std::cout << to_json(vp::ExerciseStyle::american);
 *  // american
 *  @endcode
 */
inline std::string to_str(vp::ExerciseStyle obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::ExerciseStyle object.
 */
inline vp::ExerciseStyle ExerciseStyle_from_str(std::string_view str)
{
  vp::ExerciseStyle s;
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
    throw std::invalid_argument("Invalid ExerciseStyle string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::ExerciseStyle object.
 */
inline vp::ExerciseStyle ExerciseStyle_from_json(std::string_view str)
{
  vp::ExerciseStyle s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid ExerciseStyle string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'ExerciseStyle'.
 */
inline bool is_ExerciseStyle(std::string_view str)
{
  vp::ExerciseStyle s;

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