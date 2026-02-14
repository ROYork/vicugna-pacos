#pragma once
#include <string>
#include <string_view>
#include <format>
#include <stdexcept>
#include "TimeFrameUnit.h"

namespace vp {

/**
 * @brief Timeframe utilities for creating Alpaca API timeframe strings.
 *
 * This namespace provides functions and constants for creating valid timeframe
 * strings used in Alpaca API calls (e.g., "1Min", "5Hour", "1Day").
 *
 * Example usage:
 * @code
 * using namespace vp::timeframe;
 *
 * // Use constants for common cases
 * auto bars = client.get_bars("AAPL", MINUTE_1, start, end);
 *
 * // Use functions for custom amounts
 * auto bars = client.get_bars("AAPL", minutes(5), start, end);
 * auto bars = client.get_bars("AAPL", hours(2), start, end);
 *
 * // Use make() for full control with validation
 * auto bars = client.get_bars("AAPL", make(15, TimeFrameUnit::Minute), start, end);
 * @endcode
 */
namespace timeframe {

// =============================================================================
// Common Timeframe Constants
// =============================================================================

/// One minute timeframe: "1Min"
inline constexpr std::string_view MINUTE_1 = "1Min";

/// One hour timeframe: "1Hour"
inline constexpr std::string_view HOUR_1 = "1Hour";

/// One day timeframe: "1Day"
inline constexpr std::string_view DAY_1 = "1Day";

/// One week timeframe: "1Week"
inline constexpr std::string_view WEEK_1 = "1Week";

/// One month timeframe: "1Month"
inline constexpr std::string_view MONTH_1 = "1Month";

// =============================================================================
// Validation Function
// =============================================================================

/**
 * @brief Validates a timeframe amount and unit combination.
 *
 * Validates that the amount and unit combination is valid according to
 * Alpaca API requirements:
 * - Minute: 1-59
 * - Hour: 1-23
 * - Day: 1 only
 * - Week: 1 only
 * - Month: 1, 2, 3, 6, or 12 only
 *
 * @param amount The number of time units
 * @param unit The time unit type
 * @throws std::invalid_argument if the combination is invalid
 */
inline void validate(int amount, TimeFrameUnit unit) {
    if (amount <= 0) {
        throw std::invalid_argument("Amount must be a positive integer value.");
    }

    if (unit == TimeFrameUnit::Minute && amount > 59) {
        throw std::invalid_argument("Minute units can only be used with amounts between 1-59.");
    }

    if (unit == TimeFrameUnit::Hour && amount > 23) {
        throw std::invalid_argument("Hour units can only be used with amounts 1-23.");
    }

    if ((unit == TimeFrameUnit::Day || unit == TimeFrameUnit::Week) && amount != 1) {
        throw std::invalid_argument("Day and Week units can only be used with amount 1.");
    }

    if (unit == TimeFrameUnit::Month) {
        if (amount != 1 && amount != 2 && amount != 3 && amount != 6 && amount != 12) {
            throw std::invalid_argument("Month units can only be used with amounts 1, 2, 3, 6, or 12.");
        }
    }
}

// =============================================================================
// Timeframe String Generation Functions
// =============================================================================

/**
 * @brief Creates a timeframe string with validation.
 *
 * Creates a timeframe string in the format required by Alpaca API (e.g., "5Min", "1Hour").
 * Validates the amount and unit combination before creating the string.
 *
 * @param amount The number of time units
 * @param unit The time unit type
 * @return A string representing the timeframe (e.g., "5Min", "1Hour")
 * @throws std::invalid_argument if the combination is invalid
 *
 * @code
 * auto tf = make(5, TimeFrameUnit::Minute);  // Returns "5Min"
 * auto tf = make(1, TimeFrameUnit::Hour);    // Returns "1Hour"
 * @endcode
 */
inline std::string make(int amount, TimeFrameUnit unit) {
    validate(amount, unit);
    return std::format("{}{}", amount, to_str(unit));
}

/**
 * @brief Creates a minute-based timeframe string.
 *
 * @param n Number of minutes (1-59, default 1)
 * @return A string like "1Min", "5Min", etc.
 * @throws std::invalid_argument if n is not in range 1-59
 */
inline std::string minutes(int n = 1) {
    return make(n, TimeFrameUnit::Minute);
}

/**
 * @brief Creates an hour-based timeframe string.
 *
 * @param n Number of hours (1-23, default 1)
 * @return A string like "1Hour", "5Hour", etc.
 * @throws std::invalid_argument if n is not in range 1-23
 */
inline std::string hours(int n = 1) {
    return make(n, TimeFrameUnit::Hour);
}

/**
 * @brief Creates a day timeframe string.
 *
 * @return "1Day"
 */
inline std::string day() {
    return std::string(DAY_1);
}

/**
 * @brief Creates a week timeframe string.
 *
 * @return "1Week"
 */
inline std::string week() {
    return std::string(WEEK_1);
}

/**
 * @brief Creates a month-based timeframe string.
 *
 * @param n Number of months (must be 1, 2, 3, 6, or 12, default 1)
 * @return A string like "1Month", "3Month", "6Month", or "12Month"
 * @throws std::invalid_argument if n is not 1, 2, 3, 6, or 12
 */
inline std::string months(int n = 1) {
    return make(n, TimeFrameUnit::Month);
}

} // namespace timeframe
} // namespace vp