#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the various states an Order can be in.
 *
 * please see https://alpaca.markets/docs/api-references/broker-api/trading/orders/#order-status for more info
 */
enum class OrderStatus
{
  new_,               ///< "new"
  partially_filled,   ///< "partially_filled"
  filled,             ///< "filled"
  done_for_day,       ///< "done_for_day"
  canceled,           ///< "canceled"
  expired,            ///< "expired"
  replaced,           ///< "replaced"
  pending_cancel,     ///< "pending_cancel"
  pending_replace,    ///< "pending_replace"
  pending_review,     ///< "pending_review"
  accepted,           ///< "accepted"
  pending_new,        ///< "pending_new"
  accepted_for_bidding,///< "accepted_for_bidding"
  stopped,            ///< "stopped"
  rejected,           ///< "rejected"
  suspended,          ///< "suspended"
  calculated,         ///< "calculated"
  held                ///< "held"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::OrderStatus obj);
std::string to_str(vp::OrderStatus obj);
vp::OrderStatus OrderStatus_from_str(std::string_view str);
vp::OrderStatus OrderStatus_from_json(std::string_view str);
bool is_OrderStatus(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for OrderStatus
template <>
struct glz::meta<vp::OrderStatus>
{
  using enum vp::OrderStatus;
  static constexpr auto value = glz::enumerate(
    new_,
    partially_filled,
    filled,
    done_for_day,
    canceled,
    expired,
    replaced,
    pending_cancel,
    pending_replace,
    pending_review,
    accepted,
    pending_new,
    accepted_for_bidding,
    stopped,
    rejected,
    suspended,
    calculated,
    held
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "new" or "partially_filled" for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderStatus::new_);
 *  // "new"
 *  @endcode
 */
inline std::string to_json(vp::OrderStatus obj)
{
  if (obj == vp::OrderStatus::new_) {
    return "\"new\"";
  }
  return glz::write_json(obj).value_or("OrderStatus::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns new or partially_filled for this enum.
 *  @code
 *  std::cout << to_json(vp::OrderStatus::new_);
 *  // new
 *  @endcode
 */
inline std::string to_str(vp::OrderStatus obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::OrderStatus object.
 */
inline vp::OrderStatus OrderStatus_from_str(std::string_view str)
{
  if (str == "new") {
    return vp::OrderStatus::new_;
  }
  vp::OrderStatus s;
  const std::string json = std::string("\"") + std::string(str) + std::string("\"");
  auto error = glz::read_json(s, json);
  if (error)
  {
    throw std::invalid_argument("Invalid OrderStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::OrderStatus object.
 */
inline vp::OrderStatus OrderStatus_from_json(std::string_view str)
{
  if (str == "new") {
    return vp::OrderStatus::new_;
  }
  vp::OrderStatus s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    throw std::invalid_argument("Invalid OrderStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'OrderStatus'.
 */
inline bool is_OrderStatus(std::string_view str)
{
  if (str == "new" || str == "\"new\"") {
    return true;
  }
  vp::OrderStatus s;

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