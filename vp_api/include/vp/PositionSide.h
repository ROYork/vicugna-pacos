#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what side this position is.
 */
enum class PositionSide
{
  short_, ///< "short"
  long_   ///< "long"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::PositionSide obj);
std::string to_str(vp::PositionSide obj);
vp::PositionSide PositionSide_from_str(std::string_view str);
vp::PositionSide PositionSide_from_json(std::string_view str);
bool is_PositionSide(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for PositionSide
template <>
struct glz::meta<vp::PositionSide>
{
  using enum vp::PositionSide;
  static constexpr auto value = glz::enumerate(
    short_,
    long_
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "short" or "long" for this enum.
 *  @code
 *  std::cout << to_json(vp::PositionSide::short_);
 *  // "short"
 *  @endcode
 */
inline std::string to_json(vp::PositionSide obj)
{
  if (obj == vp::PositionSide::short_) {
    return "\"short\"";
  }
  if (obj == vp::PositionSide::long_) {
    return "\"long\"";
  }
  return glz::write_json(obj).value_or("PositionSide::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns short or long for this enum.
 *  @code
 *  std::cout << to_json(vp::PositionSide::short_);
 *  // short
 *  @endcode
 */
inline std::string to_str(vp::PositionSide obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::PositionSide object.
 */
inline vp::PositionSide PositionSide_from_str(std::string_view str)
{
  if (str == "short") {
    return vp::PositionSide::short_;
  }
  if (str == "long") {
    return vp::PositionSide::long_;
  }
  vp::PositionSide s;
  const std::string json = std::string("\"") + std::string(str) + std::string("\"");
  auto error = glz::read_json(s, json);
  if (error)
  {
    throw std::invalid_argument("Invalid PositionSide string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::PositionSide object.
 */
inline vp::PositionSide PositionSide_from_json(std::string_view str)
{
  if (str == "short") {
    return vp::PositionSide::short_;
  }
  if (str == "long") {
    return vp::PositionSide::long_;
  }
  vp::PositionSide s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    throw std::invalid_argument("Invalid PositionSide string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'PositionSide'.
 */
inline bool is_PositionSide(std::string_view str)
{
  if (str == "short" || str == "\"short\"") {
    return true;
  }
  if (str == "long" || str == "\"long\"") {
    return true;
  }
  vp::PositionSide s;

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