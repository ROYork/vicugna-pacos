#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Crypto location
 */
enum class CryptoFeed
{
  us ///< "us"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::CryptoFeed obj);
std::string to_str(vp::CryptoFeed obj);
vp::CryptoFeed CryptoFeed_from_str(std::string_view str);
vp::CryptoFeed CryptoFeed_from_json(std::string_view str);
bool is_CryptoFeed(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for CryptoFeed
template <>
struct glz::meta<vp::CryptoFeed>
{
  using enum vp::CryptoFeed;
  static constexpr auto value = glz::enumerate(
    us
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "us" for this enum.
 *  @code
 *  std::cout << to_json(vp::CryptoFeed::us);
 *  // "us"
 *  @endcode
 */
inline std::string to_json(vp::CryptoFeed obj)
{
  return glz::write_json(obj).value_or("CryptoFeed::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns us for this enum.
 *  @code
 *  std::cout << to_json(vp::CryptoFeed::us);
 *  // us
 *  @endcode
 */
inline std::string to_str(vp::CryptoFeed obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::CryptoFeed object.
 */
inline vp::CryptoFeed CryptoFeed_from_str(std::string_view str)
{
  vp::CryptoFeed s;
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
    throw std::invalid_argument("Invalid CryptoFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::CryptoFeed object.
 */
inline vp::CryptoFeed CryptoFeed_from_json(std::string_view str)
{
  vp::CryptoFeed s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid CryptoFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'CryptoFeed'.
 */
inline bool is_CryptoFeed(std::string_view str)
{
  vp::CryptoFeed s;

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
