#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what side this order was executed on.
 */
enum class OrderSide
{
  buy,  ///< "buy"
  sell  ///< "sell"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::OrderSide obj);
std::string to_str(vp::OrderSide obj);
vp::OrderSide OrderSide_from_str(std::string_view str);
vp::OrderSide OrderSide_from_json(std::string_view str);
bool is_OrderSide(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for OrderSide
template <>
struct glz::meta<vp::OrderSide>
{
  using enum vp::OrderSide;
  static constexpr auto value = glz::enumerate(
    buy,
    sell
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "buy" or "sell" for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderSide::buy);
 *  // "buy"
 *  @endcode
 */
inline std::string to_json(vp::OrderSide obj)
{
  return glz::write_json(obj).value_or("OrderSide::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns buy or sell for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderSide::buy);
 *  // buy
 *  @endcode
 */
inline std::string to_str(vp::OrderSide obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::OrderSide object.
 */
inline vp::OrderSide OrderSide_from_str(std::string_view str)
{
  vp::OrderSide s;
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
    throw std::invalid_argument("Invalid OrderSide string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::OrderSide object.
 */
inline vp::OrderSide OrderSide_from_json(std::string_view str)
{
  vp::OrderSide s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid OrderSide string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'OrderSide'.
 */
inline bool is_OrderSide(std::string_view str)
{
  vp::OrderSide s;

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