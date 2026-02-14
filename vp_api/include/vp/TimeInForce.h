#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the various time in force options for an Order.
 *
 * The Time-In-Force values supported by Alpaca vary based on the order's security type. Here is a breakdown of the supported TIFs for each specific security type:
 * - Equity trading: day, gtc, opg, cls, ioc, fok.
 * - Options trading: day.
 * - Crypto trading: gtc, ioc.
 * Below are the descriptions of each TIF:
 * - day: A day order is eligible for execution only on the day it is live. By default, the order is only valid during Regular Trading Hours (9:30am - 4:00pm ET). If unfilled after the closing auction, it is automatically canceled. If submitted after the close, it is queued and submitted the following trading day. However, if marked as eligible for extended hours, the order can also execute during supported extended hours.
 * - gtc: The order is good until canceled. Non-marketable GTC limit orders are subject to price adjustments to offset corporate actions affecting the issue. We do not currently support Do Not Reduce(DNR) orders to opt out of such price adjustments.
 * - opg: Use this TIF with a market/limit order type to submit “market on open” (MOO) and “limit on open” (LOO) orders. This order is eligible to execute only in the market opening auction. Any unfilled orders after the open will be cancelled. OPG orders submitted after 9:28am but before 7:00pm ET will be rejected. OPG orders submitted after 7:00pm will be queued and routed to the following day’s opening auction. On open/on close orders are routed to the primary exchange. Such orders do not necessarily execute exactly at 9:30am / 4:00pm ET but execute per the exchange’s auction rules.
 * - cls: Use this TIF with a market/limit order type to submit “market on close” (MOC) and “limit on close” (LOC) orders. This order is eligible to execute only in the market closing auction. Any unfilled orders after the close will be cancelled. CLS orders submitted after 3:50pm but before 7:00pm ET will be rejected. CLS orders submitted after 7:00pm will be queued and routed to the following day’s closing auction. Only available with API v2.
 * - ioc: An Immediate Or Cancel (IOC) order requires all or part of the order to be executed immediately. Any unfilled portion of the order is canceled. Only available with API v2. Most market makers who receive IOC orders will attempt to fill the order on a principal basis only, and cancel any unfilled balance. On occasion, this can result in the entire order being cancelled if the market maker does not have any existing inventory of the security in question.
 * - fok: A Fill or Kill (FOK) order is only executed if the entire order quantity can be filled, otherwise the order is canceled. Only available with API v2.
 */
enum class TimeInForce
{
  day, ///< "day"
  gtc, ///< "gtc"
  opg, ///< "opg"
  cls, ///< "cls"
  ioc, ///< "ioc"
  fok  ///< "fok"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::TimeInForce obj);
std::string to_str(vp::TimeInForce obj);
vp::TimeInForce TimeInForce_from_str(std::string_view str);
vp::TimeInForce TimeInForce_from_json(std::string_view str);
bool is_TimeInForce(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for TimeInForce
template <>
struct glz::meta<vp::TimeInForce>
{
  using enum vp::TimeInForce;
  static constexpr auto value = glz::enumerate(
    day,
    gtc,
    opg,
    cls,
    ioc,
    fok
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "day" or "gtc" for this enum.
 *  @code
 *  std::cout << to_json(vp::TimeInForce::day);
 *  // "day"
 *  @endcode
 */
inline std::string to_json(vp::TimeInForce obj)
{
  return glz::write_json(obj).value_or("TimeInForce::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns day or gtc for this enum.
 *  @code
 *  std::cout << to_json(vp::TimeInForce::day);
 *  // day
 *  @endcode
 */
inline std::string to_str(vp::TimeInForce obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::TimeInForce object.
 */
inline vp::TimeInForce TimeInForce_from_str(std::string_view str)
{
  vp::TimeInForce s;
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
    throw std::invalid_argument("Invalid TimeInForce string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::TimeInForce object.
 */
inline vp::TimeInForce TimeInForce_from_json(std::string_view str)
{
  vp::TimeInForce s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid TimeInForce string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'TimeInForce'.
 */
inline bool is_TimeInForce(std::string_view str)
{
  vp::TimeInForce s;

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