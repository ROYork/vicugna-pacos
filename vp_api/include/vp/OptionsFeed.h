#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The source feed of the data.
 * `opra` requires subscription
 */
enum class OptionsFeed
{
  opra,      ///< "opra"
  indicative ///< "indicative"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::OptionsFeed obj);
std::string to_str(vp::OptionsFeed obj);
vp::OptionsFeed OptionsFeed_from_str(std::string_view str);
vp::OptionsFeed OptionsFeed_from_json(std::string_view str);
bool is_OptionsFeed(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for OptionsFeed
template <>
struct glz::meta<vp::OptionsFeed>
{
  using enum vp::OptionsFeed;
  static constexpr auto value = glz::enumerate(
    opra,
    indicative
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "opra" or "indicative" for this enum.
 *  @code
 *  std::cout << to_json(vp::OptionsFeed::opra);
 *  // "opra"
 *  @endcode
 */
inline std::string to_json(vp::OptionsFeed obj)
{
  return glz::write_json(obj).value_or("OptionsFeed::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns opra or indicative for this enum.
 *  @code
 *  std::cout << to_json(vp::OptionsFeed::opra);
 *  // opra
 *  @endcode
 */
inline std::string to_str(vp::OptionsFeed obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::OptionsFeed object.
 */
inline vp::OptionsFeed OptionsFeed_from_str(std::string_view str)
{
  vp::OptionsFeed s;
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
    throw std::invalid_argument("Invalid OptionsFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::OptionsFeed object.
 */
inline vp::OptionsFeed OptionsFeed_from_json(std::string_view str)
{
  vp::OptionsFeed s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid OptionsFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'OptionsFeed'.
 */
inline bool is_OptionsFeed(std::string_view str)
{
  vp::OptionsFeed s;

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
