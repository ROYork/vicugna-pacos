#include <gtest/gtest.h>

#include "vp/AlpacaTime.h"

using namespace date;
using namespace vp;


// A test fixture class for our timestamp parser tests
class ParseTimestampTest : public ::testing::Test {};


TEST_F(ParseTimestampTest, HandlesUTCWithNanoseconds)
{

  const std::string ts = "2025-08-15T19:30:05.123456789Z";
  using namespace date;
  // Expected timepoint construction
  auto expected_tp = sys_days{2025_y/August/15} + 19_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  vp::timepoint_t result;
  ASSERT_NO_THROW(result = vp::from_zulu(ts));
  ASSERT_EQ(result, expected_tp);

}

TEST_F(ParseTimestampTest, HandlesUTCWithNanosecondsUTC)
{

  const std::string ts = "2025-08-15T19:30:05.123456789UTC";
  using namespace date;
  // Expected timepoint construction
  auto expected_tp = sys_days{2025_y/August/15} + 19_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  vp::timepoint_t result;
  ASSERT_NO_THROW(result = vp::from_zulu(ts));
  ASSERT_EQ(result, expected_tp);

}

TEST_F(ParseTimestampTest, HandlesUTCWithNanosecondsUTCNoT)
{

  const std::string ts = "2025-08-15 19:30:05.123456789UTC";
  using namespace date;
  // Expected timepoint construction
  auto expected_tp = sys_days{2025_y/August/15} + 19_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  vp::timepoint_t result;
  ASSERT_NO_THROW(result = vp::parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);

}

TEST_F(ParseTimestampTest, HandlesUTCWithNanoseconds_PTS)
{

  const std::string ts = "2025-08-15T19:30:05.123456789Z";
  using namespace date;
  // Expected timepoint construction
  auto expected_tp = sys_days{2025_y/August/15} + 19_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  vp::timepoint_t result;
  ASSERT_NO_THROW(result = vp::parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);

}

TEST_F(ParseTimestampTest, HandlesUTCWithMicroseconds)
{
  const std::string ts = "2024-02-29T12:00:00.123456Z"; // Leap year
  auto expected_tp = sys_days{2024_y/February/29} + 12_h +std::chrono::microseconds(123456);

  timepoint_t result;
  ASSERT_NO_THROW(result = from_zulu(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesUTCWithMicroseconds_PTS)
{
  const std::string ts = "2024-02-29T12:00:00.123456Z"; // Leap year
  auto expected_tp = sys_days{2024_y/February/29} + 12_h +std::chrono::microseconds(123456);

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}


TEST_F(ParseTimestampTest, HandlesUTCWithMilliseconds)
{
  const std::string ts = "2025-01-01T00:00:00.500Z";
  auto expected_tp = sys_days{2025_y/January/1} + std::chrono::milliseconds(500);

  timepoint_t result;
  ASSERT_NO_THROW(result = from_zulu(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesUTCWithMilliseconds_PTS)
{
  const std::string ts = "2025-01-01T00:00:00.500Z";
  auto expected_tp = sys_days{2025_y/January/1} + std::chrono::milliseconds(500);

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesUTCWithNoFractionalSeconds)
{
  const std::string ts = "2025-12-31T23:59:59Z";
  auto expected_tp = sys_days{2025_y/December/31} + 23_h +59_min +59_s;

  timepoint_t result;
  ASSERT_NO_THROW(result = from_zulu(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, ZuluUTC_RndTrip)
{
  const std::string zuluTime = "2025-12-31T23:59:59Z";
  const std::string UTCTime  = "2025-12-31T23:59:59UTC";

  EXPECT_EQ(from_zulu(UTCTime),from_zulu(zuluTime));

  timepoint_t result = from_zulu(zuluTime);
  std::string strFromZulu = std::format("{:%Y-%m-%dT%H:%M:%S%Z}", result);

  EXPECT_EQ(from_zulu(UTCTime),from_zulu(strFromZulu));

}

// --- Tests for Valid Offset Timestamps ---


TEST_F(ParseTimestampTest, HandlesNegativeOffsetWithColon)
{
  // 19:30 in -04:00 timezone is 23:30 UTC
  const std::string ts = "2025-08-15T19:30:05.123456789-04:00";
  auto expected_tp = sys_days{2025_y/August/15} + 23_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  timepoint_t result;
  ASSERT_NO_THROW(result = from_offset(ts));
  ASSERT_EQ(result, expected_tp);
}
TEST_F(ParseTimestampTest, HandlesNegativeOffsetWithColon_PTS)
{
  // 19:30 in -04:00 timezone is 23:30 UTC
  const std::string ts = "2025-08-15T19:30:05.123456789-04:00";
  auto expected_tp = sys_days{2025_y/August/15} + 23_h +30_min +5_s +std::chrono::nanoseconds(123456789);

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesPositiveOffsetWithColon) {
  // 02:00 in +05:30 timezone is the previous day 20:30 UTC
  const std::string ts = "2025-08-16T02:00:00.500+05:30";
  auto expected_tp = sys_days{2025_y/August/15} + 20_h +30_min +std::chrono::milliseconds(500);

  timepoint_t result;
  ASSERT_NO_THROW(result = from_offset(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesPositiveOffsetWithColon_PTS) {
  // 02:00 in +05:30 timezone is the previous day 20:30 UTC
  const std::string ts = "2025-08-16T02:00:00.500+05:30";
  auto expected_tp = sys_days{2025_y/August/15} + 20_h +30_min +std::chrono::milliseconds(500);

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesPositiveOffsetWithColon_PTS_no_T) {
  // 02:00 in +05:30 timezone is the previous day 20:30 UTC
  const std::string ts = "2025-08-16 02:00:00.500+05:30";
  auto expected_tp = sys_days{2025_y/August/15} + 20_h +30_min +std::chrono::milliseconds(500);

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesNegativeOffsetWithoutColon) {
  // 10:00 in -0500 timezone is 15:00 UTC
  const std::string ts = "2025-08-15T10:00:00-0500";
  auto expected_tp = sys_days{2025_y/August/15} + 15_h;

  timepoint_t result;
  ASSERT_NO_THROW(result = from_offset(ts));
  ASSERT_EQ(result, expected_tp);
}

TEST_F(ParseTimestampTest, HandlesNegativeOffsetWithoutColon_PTS) {
  // 10:00 in -0500 timezone is 15:00 UTC
  const std::string ts = "2025-08-15T10:00:00-0500";
  auto expected_tp = sys_days{2025_y/August/15} + 15_h;

  timepoint_t result;
  ASSERT_NO_THROW(result = parse_timestamp(ts));
  ASSERT_EQ(result, expected_tp);
}

// --- Tests for Invalid and Malformed Timestamps ---

TEST_F(ParseTimestampTest, ThrowsOnEmptyString) {
  ASSERT_THROW(from_offset(""), std::runtime_error);
}

TEST_F(ParseTimestampTest, ThrowsOnMalformedDate) {
  ASSERT_THROW(from_zulu("2025-13-15T10:00:00Z"), std::runtime_error); // Invalid month
}

TEST_F(ParseTimestampTest, ThrowsOnMalformedTime) {
  ASSERT_THROW(from_zulu("2025-12-15T25:00:00Z"), std::runtime_error); // Invalid hour
}

TEST_F(ParseTimestampTest, ThrowsOnIncorrectSeparator) {
  ASSERT_THROW(from_zulu("2025-12-15 10:00:00Z"), std::runtime_error); // Space instead of T
}

// TEST_F(ParseTimestampTest, ThrowsOnExtraCharactersAtEnd) {
//   ASSERT_THROW(from_zulu("2025-12-15T10:00:00Z-extra"), std::runtime_error);
// }

TEST_F(ParseTimestampTest, ThrowsOnIncompleteString) {
  ASSERT_THROW(from_zulu("2025-12-15T10:00"), std::runtime_error);
}

TEST_F(ParseTimestampTest, ThrowsOnNonTimestampString) {
  ASSERT_THROW(from_zulu("this is not a timestamp"), std::runtime_error);
}

TEST_F(ParseTimestampTest, ThrowsOnOffsetWithZ) {
  // The format is ambiguous and should fail the strict parse
  ASSERT_THROW(from_offset("2025-08-15T19:30:05.123Z-04:00"), std::runtime_error);
}

//Grok3 tests

// The parse_iso8601 function to be tested
timepoint_t parse_iso8601(const std::string& str) {
  using namespace date;
  using namespace std::chrono;

  std::istringstream iss(str);
  timepoint_t tp;
  // Using %f for fractional seconds to handle nanosecond precision
  iss >> parse("%Y-%m-%dT%H:%M:%S.%f%z", tp);
  if (iss.fail()) {
    throw std::runtime_error("Failed to parse ISO 8601 timestamp");
  }
  return tp;
}

// Test valid Zulu time parsing
TEST_F(ParseTimestampTest, UNIX_EPOCH_ToEpochZero)
{
  timepoint_t tp = UNIX_EPOCH;
  int64_t expected_nanos = 0LL;
  EXPECT_EQ(to_epoch_nanos(tp), expected_nanos);
}

// Test invalid format throws exception
TEST_F(ParseTimestampTest, ThrowsOnInvalidFormat) {
  std::string invalid_time = "2025-07-25 15:15:00Z"; // Missing 'T'
  EXPECT_THROW(parse_iso8601(invalid_time), std::runtime_error);
}

// Test empty string throws exception
TEST_F(ParseTimestampTest, ThrowsOnEmptyStringG3) {
  std::string empty_time = "";
  EXPECT_THROW(parse_iso8601(empty_time), std::runtime_error);
}

// Test invalid date throws exception
TEST_F(ParseTimestampTest, ThrowsOnInvalidDate) {
  std::string invalid_date = "2025-13-25T15:15:00Z"; // Invalid month
  EXPECT_THROW(parse_iso8601(invalid_date), std::runtime_error);
}



