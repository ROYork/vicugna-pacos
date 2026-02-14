#pragma once

#include "vp/AlpacaTime.h"
#include <glaze/glaze.hpp>
#include <iostream>

namespace vp {

struct Clock
{
  std::string timestamp  = vp::strEpoch();
  bool is_open           = false;
  std::string next_open  = vp::strEpoch();
  std::string next_close = vp::strEpoch();

  timepoint_t ts() const       {return vp::parse_timestamp(timestamp);}
  timepoint_t nextOpen() const {return vp::parse_timestamp(next_open);}
  timepoint_t nextClose() const{return vp::parse_timestamp(next_close);}

  std::string to_json() const;
  static Clock from_json(const std::string &jsonStr);

  // Three-way comparison operator
  std::strong_ordering operator<=>(const Clock& other) const = default;
};

} // namespace vp

// Outside of alpaca namespace
template <>
struct glz::meta<vp::Clock>
{
  using T = vp::Clock;
  static constexpr auto value = glz::object(
    "timestamp", &T::timestamp,
    "is_open", &T::is_open,
    "next_open", &T::next_open,
    "next_close", &T::next_close
  );
};

/**
 * @brief Converts this class to json
 */
inline std::string vp::Clock::to_json() const
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

/**
 * @brief Creates a \c Clock class from a JSON string
 */
inline vp::Clock vp::Clock::from_json(const std::string &jsonStr)
{
  vp::Clock obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse Clock JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
