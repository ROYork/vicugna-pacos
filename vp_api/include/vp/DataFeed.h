#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Equity market data feeds. OTC and SIP are available with premium data subscriptions.
 */
enum class DataFeed
{
  iex,        ///< "iex"
  sip,        ///< "sip"
  delayed_sip,///< "delayed_sip"
  otc,        ///< "otc"
  boats,      ///< "boats"
  overnight   ///< "overnight"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::DataFeed obj);
std::string to_str(vp::DataFeed obj);
vp::DataFeed DataFeed_from_str(std::string_view str);
vp::DataFeed DataFeed_from_json(std::string_view str);
bool is_DataFeed(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for DataFeed
template <>
struct glz::meta<vp::DataFeed>
{
  using enum vp::DataFeed;
  static constexpr auto value = glz::enumerate(
    iex,
    sip,
    delayed_sip,
    otc,
    boats,
    overnight
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "iex" or "sip" for this enum.
 *  @code
 *  std::cout << to_json(vp::DataFeed::iex);
 *  // "iex"
 *  @endcode
 */
inline std::string to_json(vp::DataFeed obj)
{
  return glz::write_json(obj).value_or("DataFeed::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns iex or sip for this enum.
 *  @code
 *  std::cout << to_json(vp::DataFeed::iex);
 *  // iex
 *  @endcode
 */
inline std::string to_str(vp::DataFeed obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::DataFeed object.
 */
inline vp::DataFeed DataFeed_from_str(std::string_view str)
{
  vp::DataFeed s;
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
    throw std::invalid_argument("Invalid DataFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::DataFeed object.
 */
inline vp::DataFeed DataFeed_from_json(std::string_view str)
{
  vp::DataFeed s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid DataFeed string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'DataFeed'.
 */
inline bool is_DataFeed(std::string_view str)
{
  vp::DataFeed s;

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
