#pragma once
#include <glaze/glaze.hpp>


// From Common Module

namespace vp {




/**
 * @brief An enum for choosing what type of pagination of results you'd like for BrokerClient functions that support
 *   pagination.
 *
 *   Attributes:
 *      none: Requests that we perform no pagination of results and just return the single response the API gave us.
 *     full: Requests that we perform all the pagination and return just a single List/dict/etc containing all the
 *        results. This is the default for most functions.
 *      iterator: Requests that we return an Iterator that yields one "page" of results at a time
 */
enum class PaginationType
{
  none,
  full,
  iterator
};

/**
 * @brief An enum for sorting results in ascending or descending order.
 */
enum class Sort
{
  asc,
  desc
};



} // End alpaca namespace



//Function declarations



std::string to_json(vp::PaginationType obj);
std::string to_str(vp::PaginationType obj);
vp::PaginationType PaginationType_from_str(std::string_view str);
vp::PaginationType PaginationType_from_json(std::string_view str);
bool is_PaginationType(std::string_view str);

std::string to_json(vp::Sort obj);
std::string to_str(vp::Sort obj);
vp::Sort Sort_from_str(std::string_view str);
vp::Sort Sort_from_json(std::string_view str);
bool is_Sort(std::string_view str);










/// glz::meta information is outside the alpaca namespace
template <>
struct glz::meta<vp::PaginationType>
{
  using enum vp::PaginationType;
  static constexpr auto value = glz::enumerate(
    none,
    full,
    iterator
    );
};

/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "none", "full" or "iterator" for this enum.
 *  @code
 *  std::cout << to_json(vp::PaginationType::full);
 *  // "full"
 *  @endcode
 */
inline std::string to_json(vp::PaginationType obj)
{
  return glz::write_json(obj).value_or("PaginationType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns none, full or iterator for this enum.
 *  @code
 *  std::cout << to_str(vp::PaginationType::full);
 *  // full
 *  @endcode
 */
inline std::string to_str(vp::PaginationType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::PaginationType object.
 */
inline vp::PaginationType PaginationType_from_str(std::string_view str)
{
  vp::PaginationType s;
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
    throw std::invalid_argument("Invalid PaginationType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::PaginationType object.
 */
inline vp::PaginationType PaginationType_from_json(std::string_view str)
{
  vp::PaginationType s;
  const std::string json = "\"" + std::string(str) + "\"";
  auto error = glz::read_json(s, json);
  if (error)
  {
    auto error2 = glz::read_json(s, str);
    if(!error2)
     {
       return s;
     }
    throw std::invalid_argument("Invalid PaginationType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'PaginationType'.
 */
bool is_PaginationType(std::string_view str)
{
  vp::PaginationType s;

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



/// glz::meta information is outside the alpaca namespace
template <>
struct glz::meta<vp::Sort>
{
  using enum vp::Sort;
  static constexpr auto value = glz::enumerate(
    asc,
    desc
    );
};

/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "asc" or "desc" for this enum.
 *  @code
 *  std::cout << to_json(vp::Sort::asc);
 *  // "asc"
 *  @endcode
 */
inline std::string to_json(vp::Sort obj)
{
  return glz::write_json(obj).value_or("\"Sort::to_json::error\"");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns asc or desc for this enum.
 *  @code
 *  std::cout << to_str(vp::Sort::asc);
 *  // asc
 *  @endcode
 */
inline std::string to_str(vp::Sort obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::Sort object.
 */
inline vp::Sort Sort_from_str(std::string_view str)
{
  vp::Sort s;
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
    throw std::invalid_argument("Invalid Sort string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::Sort object.
 */
inline vp::Sort Sort_from_json(std::string_view str)
{
  vp::Sort s;
  const std::string json = "\"" + std::string(str) + "\"";
  auto error = glz::read_json(s, json);
  if (error)
  {
    auto error2 = glz::read_json(s, str);
    if(!error2)
     {
       return s;
     }
    throw std::invalid_argument("Invalid Sort string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'Sort'.
 */
bool is_Sort(std::string_view str)
{
  vp::Sort s;

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



