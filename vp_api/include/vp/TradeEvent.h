#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents a trade event.
 */
enum class TradeEvent
{
  fill,         ///< "fill"
  canceled,     ///< "canceled"
  pending_new,  ///< "pending_new"
  new_,         ///< "new"
  partial_fill  ///< "partial_fill"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::TradeEvent obj);
std::string to_str(vp::TradeEvent obj);
vp::TradeEvent TradeEvent_from_str(std::string_view str);
vp::TradeEvent TradeEvent_from_json(std::string_view str);
bool is_TradeEvent(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for TradeEvent
template <>
struct glz::meta<vp::TradeEvent>
{
  using enum vp::TradeEvent;
  static constexpr auto value = glz::enumerate(
    fill,
    canceled,
    pending_new,
    new_,
    partial_fill
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "fill" or "canceled" for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeEvent::fill);
 *  // "fill"
 *  @endcode
 */
inline std::string to_json(vp::TradeEvent obj)
{
  if (obj == vp::TradeEvent::new_) {
    return "\"new\"";
  }
  return glz::write_json(obj).value_or("TradeEvent::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns fill or canceled for this enum.
 *  @code
 *  std::cout << to_json(vp::TradeEvent::fill);
 *  // fill
 *  @endcode
 */
inline std::string to_str(vp::TradeEvent obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::TradeEvent object.
 */
inline vp::TradeEvent TradeEvent_from_str(std::string_view str)
{
  if (str == "new") {
    return vp::TradeEvent::new_;
  }
  vp::TradeEvent s;
  const std::string json = "\"" + std::string(str) + "\"";
  auto error = glz::read_json(s, json);
  if (error)
  {
    throw std::invalid_argument("Invalid TradeEvent string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::TradeEvent object.
 */
inline vp::TradeEvent TradeEvent_from_json(std::string_view str)
{
  if (str == "\"new\"") {
    return vp::TradeEvent::new_;
  }
  vp::TradeEvent s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    throw std::invalid_argument("Invalid TradeEvent string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'TradeEvent'.
 */
inline bool is_TradeEvent(std::string_view str)
{
  if (str == "new" || str == "\"new\"") {
    return true;
  }
  vp::TradeEvent s;

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