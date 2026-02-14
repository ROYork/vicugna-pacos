#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what side this order was executed on.
 */
enum class PositionIntent
{
  buy_to_open,   ///< "buy_to_open"
  buy_to_close,  ///< "buy_to_close"
  sell_to_open,  ///< "sell_to_open"
  sell_to_close  ///< "sell_to_close"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::PositionIntent obj);
std::string to_str(vp::PositionIntent obj);
vp::PositionIntent PositionIntent_from_str(std::string_view str);
vp::PositionIntent PositionIntent_from_json(std::string_view str);
bool is_PositionIntent(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for PositionIntent
template <>
struct glz::meta<vp::PositionIntent>
{
  using enum vp::PositionIntent;
  static constexpr auto value = glz::enumerate(
    buy_to_open,
    buy_to_close,
    sell_to_open,
    sell_to_close
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "buy_to_open" or "buy_to_close" for this enum.
 *  @code
 *  std::cout << to_json(vp::PositionIntent::buy_to_open);
 *  // "buy_to_open"
 *  @endcode
 */
inline std::string to_json(vp::PositionIntent obj)
{
  return glz::write_json(obj).value_or("PositionIntent::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns buy_to_open or buy_to_close for this enum.
 *  @code
 *  std::cout << to_json(vp::PositionIntent::buy_to_open);
 *  // buy_to_open
 *  @endcode
 */
inline std::string to_str(vp::PositionIntent obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::PositionIntent object.
 */
inline vp::PositionIntent PositionIntent_from_str(std::string_view str)
{
  vp::PositionIntent s;
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
    throw std::invalid_argument("Invalid PositionIntent string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::PositionIntent object.
 */
inline vp::PositionIntent PositionIntent_from_json(std::string_view str)
{
  vp::PositionIntent s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid PositionIntent string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'PositionIntent'.
 */
inline bool is_PositionIntent(std::string_view str)
{
  vp::PositionIntent s;

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