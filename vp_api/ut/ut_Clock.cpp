#include <gtest/gtest.h>
#include "vp/Clock.h"
#include "vp/AlpacaTime.h"
#include <glaze/glaze.hpp>
#include <chrono>

 TEST(ClockTest, DefaultConstruction)
 {
     vp::Clock clock;
     // Default values for timepoint_t and bool
     ASSERT_EQ(vp::UNIX_EPOCH, clock.ts());
     ASSERT_FALSE(clock.is_open);
     ASSERT_EQ(vp::UNIX_EPOCH, clock.nextOpen());
     ASSERT_EQ(vp::UNIX_EPOCH, clock.nextClose());
 }

TEST(ClockTest, ParameterizedConstructionAndAccessors) {
    using namespace std::chrono;
    using namespace vp;

    std::string ts         = "2025-08-19T10:00:00Z";
    std::string next_open  = "2025-08-19T09:30:00Z";
    std::string next_close = "2025-08-19T16:00:00Z";

    vp::Clock clock{
        .timestamp = ts,
        .is_open = true,
        .next_open = next_open,
        .next_close = next_close
    };

    ASSERT_EQ(ts, clock.timestamp);
    ASSERT_TRUE(clock.is_open);
    ASSERT_EQ(next_open, clock.next_open);
    ASSERT_EQ(next_close, clock.next_close);
}

TEST(ClockTest, GlazeSerializationDeserialization) {

    vp::Clock original_clock{
        .timestamp = "2025-08-19T10:00:00Z",
        .is_open = true,
        .next_open = "2025-08-19T09:30:00Z",
        .next_close = "2025-08-19T16:00:00Z"
    };

    std::string json_str;
    auto error = glz::write_json(original_clock, json_str);
    ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

    vp::Clock deserialized_clock;
    error = glz::read_json(deserialized_clock, json_str);
    ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

    ASSERT_EQ(original_clock.timestamp, deserialized_clock.timestamp);
    ASSERT_EQ(original_clock.is_open, deserialized_clock.is_open);
    ASSERT_EQ(original_clock.next_open, deserialized_clock.next_open);
    ASSERT_EQ(original_clock.next_close, deserialized_clock.next_close);
}

 TEST(ClockTest, GlazeSerializationDeserialization_FalseIsOpen) {


     vp::Clock original_clock{
         .timestamp = "2025-08-19T18:00:00Z",
         .is_open = false,
         .next_open = "2025-08-20T09:30:00Z",
         .next_close = "2025-08-20T16:00:00Z"
     };

     std::string json_str;
     auto error = glz::write_json(original_clock, json_str);
     ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

     vp::Clock deserialized_clock;
     error = glz::read_json(deserialized_clock, json_str);
     ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

     ASSERT_EQ(original_clock.timestamp, deserialized_clock.timestamp);
     ASSERT_EQ(original_clock.is_open, deserialized_clock.is_open);
     ASSERT_EQ(original_clock.next_open, deserialized_clock.next_open);
     ASSERT_EQ(original_clock.next_close, deserialized_clock.next_close);
}
