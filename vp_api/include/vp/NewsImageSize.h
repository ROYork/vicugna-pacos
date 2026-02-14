#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief News image sizes.
 */
enum class NewsImageSize
{
  thumb, ///< "thumb"
  small, ///< "small"
  large  ///< "large"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::NewsImageSize obj);
std::string to_str(vp::NewsImageSize obj);
vp::NewsImageSize NewsImageSize_from_str(std::string_view str);
vp::NewsImageSize NewsImageSize_from_json(std::string_view str);
bool is_NewsImageSize(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for NewsImageSize
template <>
struct glz::meta<vp::NewsImageSize>
{
  using enum vp::NewsImageSize;
  static constexpr auto value = glz::enumerate(
    thumb,
    small,
    large
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "thumb" or "small" for this enum.
 *  @code
 *  std::cout << to_json(vp::NewsImageSize::thumb);
 *  // "thumb"
 *  @endcode
 */
inline std::string to_json(vp::NewsImageSize obj)
{
  return glz::write_json(obj).value_or("NewsImageSize::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns thumb or small for this enum.
 *  @code
 *  std::cout << to_json(vp::NewsImageSize::thumb);
 *  // thumb
 *  @endcode
 */
inline std::string to_str(vp::NewsImageSize obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::NewsImageSize object.
 */
inline vp::NewsImageSize NewsImageSize_from_str(std::string_view str)
{
  vp::NewsImageSize s;
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
    throw std::invalid_argument("Invalid NewsImageSize string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::NewsImageSize object.
 */
inline vp::NewsImageSize NewsImageSize_from_json(std::string_view str)
{
  vp::NewsImageSize s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid NewsImageSize string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'NewsImageSize'.
 */
inline bool is_NewsImageSize(std::string_view str)
{
  vp::NewsImageSize s;

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
