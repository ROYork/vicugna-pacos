#pragma once

/**
 * @file AlpacaTime.h
 * @brief Utilities for parsing and formatting ISO 8601 timestamps for Alpaca API
 *
 * This header provides functions for converting between ISO 8601 formatted strings
 * and std::chrono::time_point objects with nanosecond precision.
 *
 * Supported timestamp formats:
 * - Zulu time: "2025-07-25T15:15:00.560999329Z"
 * - UTC suffix: "2025-07-25T15:15:00.560999329UTC"
 * - Timezone offset: "2025-08-15T16:07:21.002188359-04:00"
 * - Space separator: "2025-08-15 16:07:21.002188359-04:00"
 *
 * @note Define ALPACA_NO_THROW to disable exceptions. When defined, parse errors
 *       return UNIX_EPOCH and log to std::cerr instead of throwing std::runtime_error.
 */

#include <string>
#include <string_view>
#include <chrono>
#include <sstream>
#include <iostream>
#include <format>
#include <cctype>

#include <glaze/glaze.hpp>
#include <date/date.h>

namespace vp {

constexpr std::chrono::hours operator""_h(unsigned long long H) noexcept
{
  return std::chrono::hours(H);
}
constexpr std::chrono::minutes operator""_min(unsigned long long Min) noexcept
{
  return std::chrono::minutes(Min);
}

constexpr std::chrono::seconds operator""_s(unsigned long long Sec) noexcept
{
  return std::chrono::seconds(Sec);
}

using timepoint_t = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

inline const timepoint_t UNIX_EPOCH = std::chrono::system_clock::from_time_t(0);

/**
 * @brief Utility to convert timepoint to epoch nanoseconds for comparison
 * @param tp The timepoint to convert
 * @return Nanoseconds since Unix epoch
 */
inline int64_t to_epoch_nanos(const timepoint_t& tp)
{
  return std::chrono::duration_cast<std::chrono::nanoseconds>(tp.time_since_epoch()).count();
}

/**
 * @brief Converts a timepoint to ISO 8601 formatted string with Zulu time
 * @param ts The timepoint to convert
 * @return ISO 8601 string like "2025-07-25T15:15:00Z"
 *
 * @note This function formats to microsecond precision and appends 'Z' for UTC
 */
inline std::string from_timestamp(timepoint_t ts)
{
  // Use microsecond precision for better compatibility
  auto ts_micro = std::chrono::floor<std::chrono::microseconds>(ts);
  return std::format("{:%Y-%m-%dT%H:%M:%S}Z", ts_micro);
}

/**
 * @brief Returns a static string representing the Unix epoch
 * @return "1970-01-01T00:00:00Z"
 */
inline const std::string& strEpoch()
{
  static const std::string STR_EPOCH = "1970-01-01T00:00:00Z";
  return STR_EPOCH;
}

/**
 * @brief Converts an ISO 8601 formatted string like
 * "2025-07-25T15:15:00.560999329Z" to a std::chrono::time_point.
 *
 * This function uses the Howard Hinnant date library to parse timestamps.
 * It correctly handles timestamps with fractional seconds and Zulu time (Z) suffix.
 *
 * For timestamps with timezone offsets (e.g., -04:00), use from_offset() instead.
 *
 * The format string "%Y-%m-%dT%H:%M:%S%Z" is used for parsing.
 * The format string "%Y-%m-%dT%H:%M:%S%Z" breaks down as follows:
 * %Y: Year with century (e.g., 2025)
 * %m: Month as a decimal number (01-12)
 * %d: Day of the month as a decimal number (01-31)
 * T:  The literal character 'T' which separates the date from the time.
 * %H: Hour (24-hour clock) as a decimal number (00-23)
 * %M: Minute as a decimal number (00-59)
 * %S: Second as a decimal number. std::chrono::parse automatically handles
 *     the fractional part when the target time_point has enough precision.
 * %Z: Parses the time zone abbreviation or name, taken as the longest sequence
 *     of characters that only contains the characters:
 *     A through Z, a through z, 0 through 9, -, +, _, and /.
 *
 * @param iso_string A string_view containing the ISO 8601 timestamp.
 * @return A timepoint_t object representing the parsed time, normalized to UTC.
 * @throws std::runtime_error if the string cannot be parsed.
 */
inline timepoint_t from_zulu(std::string_view iso_string)
{
  using namespace date;
  using namespace std::chrono;

  timepoint_t tp;
  std::stringstream ss;
  ss.write(iso_string.data(), iso_string.size());
  ss >> parse("%Y-%m-%dT%H:%M:%S%Z", tp);

  // Check if the stream failed during parsing. This can happen if the
  // input string does not match the specified format.
  if (ss.fail())
  {
#ifdef ALPACA_NO_THROW
    std::cerr << __FUNCTION__ << " : Failed to parse timestamp: "
              << iso_string << "\n";
    return UNIX_EPOCH;
#else
    throw std::runtime_error(std::string(__FUNCTION__) +
                             " : Failed to parse timestamp: "
                             + std::string(iso_string));
#endif
  }

  return tp;
}

/**
 * @brief Parses an ISO 8601 formatted string using an offset like:
 *  "2025-08-15T16:07:21.002188359-04:00" to a \c timepoint_t
 * @param iso_string
 * @return
 *
 * @sa timepoint_t
 * @sa from_zulu
 */
inline timepoint_t from_offset(std::string_view iso_string_with_offset)
{
  using namespace date;
  using namespace std::chrono;

  timepoint_t tp;
  std::stringstream ss;
  ss.write(iso_string_with_offset.data(), iso_string_with_offset.size());
  ss >> parse("%Y-%m-%dT%H:%M:%S%Ez", tp);

  if (ss.fail())
  {
#ifdef ALPACA_NO_THROW
    std::cerr << __FUNCTION__ << " : Failed to parse timestamp: "
              << iso_string_with_offset << "\n";
    return UNIX_EPOCH;
#else
    throw std::runtime_error(std::string(__FUNCTION__) +
                             " : Failed to parse timestamp: "
                             + std::string(iso_string_with_offset));
#endif
  }

  return tp;
}



/**
 * @brief More flexible timestamp parsing supporting multiple ISO 8601 formats
 *
 * Supports the following formats:
 * - Zulu time: "2025-07-25T15:15:00.560999329Z"
 * - UTC suffix: "2025-07-25T15:15:00.560999329UTC"
 * - UTC offset: "2025-08-15T16:07:21.002188359-04:00"
 * - Space separator: "2025-08-15 16:07:21.002188359-04:00"
 *
 * @param iso_string ISO 8601 formatted timestamp
 * @return Parsed timepoint normalized to UTC
 * @throws std::runtime_error if parsing fails (unless ALPACA_NO_THROW is defined)
 */
inline timepoint_t parse_timestamp(std::string_view iso_string)
{
  using namespace date;
  using namespace std::chrono;

  if(iso_string.empty())
  {
#ifdef ALPACA_NO_THROW
    std::cerr << __FUNCTION__
              << ": empty string passed to function, returning UNIX_EPOCH!\n";
    return UNIX_EPOCH;
#else
    throw std::runtime_error(std::string(__FUNCTION__) +
                             " : empty string passed to function!");
#endif
  }

  timepoint_t tp;
  std::stringstream ss;
  ss.write(iso_string.data(), iso_string.size());

  // Check if timestamp ends with 'Z' or "UTC" (Zulu/UTC time)
  if(iso_string.back() == 'Z' ||
     (iso_string.size() >= 3 && iso_string.substr(iso_string.size() - 3) == "UTC"))
  {
    // Zulu/UTC format: "2025-07-25T15:15:00.560999329Z" or "...UTC"

    auto lenToCol = iso_string.find_first_of(':');
    std::string_view firstHalf = iso_string.substr(0, lenToCol);

    if(firstHalf.contains('T'))
    {
      ss >> parse("%Y-%m-%dT%H:%M:%S%Z", tp);
    }
    else
    {
      ss >> parse("%Y-%m-%d %H:%M:%S%Z", tp);
    }
  }
  else
  {
    // UTC offset format: "2025-08-15T16:07:21.002188359-04:00"

    if(iso_string.contains('T'))
    {
      ss >> parse("%Y-%m-%dT%H:%M:%S%Ez", tp);
    }
    else
    {
      // Space separator: "2025-08-15 16:07:21.002188359-04:00"
      ss >> parse("%Y-%m-%d %H:%M:%S%Ez", tp);
    }
  }

  if (ss.fail())
  {
#ifdef ALPACA_NO_THROW
    std::cerr << __FUNCTION__ << " : Failed to parse timestamp: "
              << iso_string << "\n";
    return UNIX_EPOCH;
#else
    throw std::runtime_error(std::string(__FUNCTION__) +
                             " : Failed to parse timestamp: "
                             + std::string(iso_string));
#endif
  }

  return tp;
}



} // namespace vp

