#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Most actives possible filters.
 */
enum class MostActivesBy
{
  volume, ///< "volume"
  trades  ///< "trades"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::MostActivesBy obj);
std::string to_str(vp::MostActivesBy obj);
vp::MostActivesBy MostActivesBy_from_str(std::string_view str);
vp::MostActivesBy MostActivesBy_from_json(std::string_view str);
bool is_MostActivesBy(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for MostActivesBy
template <>
struct glz::meta<vp::MostActivesBy>
{
  using enum vp::MostActivesBy;
  static constexpr auto value = glz::enumerate(
    volume,
    trades
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "volume" or "trades" for this enum.
 *  @code
 *  std::cout << to_json(vp::MostActivesBy::volume);
 *  // "volume"
 *  @endcode
 */
inline std::string to_json(vp::MostActivesBy obj)
{
  return glz::write_json(obj).value_or("MostActivesBy::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns volume or trades for this enum.
 *  @code
 *  std::cout << to_json(vp::MostActivesBy::volume);
 *  // volume
 *  @endcode
 */
inline std::string to_str(vp::MostActivesBy obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::MostActivesBy object.
 */
inline vp::MostActivesBy MostActivesBy_from_str(std::string_view str)
{
  vp::MostActivesBy s;
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
    throw std::invalid_argument("Invalid MostActivesBy string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::MostActivesBy object.
 */
inline vp::MostActivesBy MostActivesBy_from_json(std::string_view str)
{
  vp::MostActivesBy s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid MostActivesBy string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'MostActivesBy'.
 */
inline bool is_MostActivesBy(std::string_view str)
{
  vp::MostActivesBy s;

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
