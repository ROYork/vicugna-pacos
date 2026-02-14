#pragma once

#include "AlpacaTime.h"
#include <glaze/glaze.hpp>

namespace vp {

/**
 * @brief Market Calendar Data
 *
 * https://paper-api.alpaca.markets/v2/calendar
 *
 * Example API Return Value
 * @code
 *  {
 *    "close": "16:00",
 *    "date": "2025-08-18",
 *    "open": "09:30",
 *    "session_close": "2000",
 *    "session_open": "0400",
 *    "settlement_date": "2025-08-19"
 *  }
 * @endcode
 */
struct Calendar
{
  /// The time the market closes at on this date in “%H:%M” format
  std::string close  = vp::strEpoch();

  /// Date string in “%Y-%m-%d” format
  std::string date  = vp::strEpoch();

  ///The time the market opens at on this date in “%H:%M” format
  std::string open  = vp::strEpoch();

  /// Date string in “%Y-%m-%d” format. Representing the settlement date for the trade date.
  std::string settlement_date = vp::strEpoch();

  timepoint_t closes();
  timepoint_t opens();
  // timepoint_t nextOpen() {return vp::parse_timestamp(next_open);}
  // timepoint_t nextClose(){return vp::parse_timestamp(next_close);}

  std::string to_json() const;
  static Calendar from_json(const std::string &jsonStr);

  // Three-way comparison operator
  std::strong_ordering operator<=>(const Calendar& other) const = default;
};

} // namespace vp

// Outside of alpaca namespace
template <>
struct glz::meta<vp::Calendar>
{
  using T = vp::Calendar;
  static constexpr auto value = glz::object(
    "close", &T::close,
    "date", &T::date,
    "open", &T::open,
    "settlement_date", &T::settlement_date
  );
};

/**
 * @brief Convert \c close property to a \c timepoint_t
 */
inline vp::timepoint_t vp::Calendar::closes()
{
  std::string closeTime =
    std::format("{}T{}:00.000000000Z", this->date, this->close);

  return vp::parse_timestamp(closeTime);
}

/**
 * @brief Convert \c open property to a \c timepoint_t
 */
inline vp::timepoint_t vp::Calendar::opens()
{
  std::string openTime =
    std::format("{}T{}:00.000000000Z", this->date, this->open);

  return vp::parse_timestamp(openTime);
}



inline std::string vp::Calendar::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    std::cerr << "error:" << __FUNCTION__
              << "json conversion failed with error: " << error;
    return std::string("");
  }
  else
  {
    return json_string;
  }
}

inline vp::Calendar vp::Calendar::from_json(const std::string &jsonStr)
{
  vp::Calendar obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse Calendar JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
