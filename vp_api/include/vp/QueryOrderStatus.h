#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the status of orders to query.
 */
enum class QueryOrderStatus
{
  open,   ///< "open"
  closed, ///< "closed"
  all     ///< "all"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::QueryOrderStatus obj);
std::string to_str(vp::QueryOrderStatus obj);
vp::QueryOrderStatus QueryOrderStatus_from_str(std::string_view str);
vp::QueryOrderStatus QueryOrderStatus_from_json(std::string_view str);
bool is_QueryOrderStatus(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for QueryOrderStatus
template <>
struct glz::meta<vp::QueryOrderStatus>
{
  using enum vp::QueryOrderStatus;
  static constexpr auto value = glz::enumerate(
    open,
    closed,
    all
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "open" or "closed" for this enum.
 *  @code
 *  std::cout << to_json(vp::QueryOrderStatus::open);
 *  // "open"
 *  @endcode
 */
inline std::string to_json(vp::QueryOrderStatus obj)
{
  return glz::write_json(obj).value_or("QueryOrderStatus::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns open or closed for this enum.
 *  @code
 *  std::cout << to_json(vp::QueryOrderStatus::open);
 *  // open
 *  @endcode
 */
inline std::string to_str(vp::QueryOrderStatus obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::QueryOrderStatus object.
 */
inline vp::QueryOrderStatus QueryOrderStatus_from_str(std::string_view str)
{
  vp::QueryOrderStatus s;
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
    throw std::invalid_argument("Invalid QueryOrderStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::QueryOrderStatus object.
 */
inline vp::QueryOrderStatus QueryOrderStatus_from_json(std::string_view str)
{
  vp::QueryOrderStatus s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid QueryOrderStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'QueryOrderStatus'.
 */
inline bool is_QueryOrderStatus(std::string_view str)
{
  vp::QueryOrderStatus s;

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