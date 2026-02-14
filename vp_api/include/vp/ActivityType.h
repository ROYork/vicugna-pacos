#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents what kind of Activity an instance of TradeActivity or NonTradeActivity is.
 *
 *   Please see https://alpaca.markets/docs/api-references/broker-api/accounts/account-activities/#enumactivitytype
 *   for descriptions of each of the types
 */
enum class ActivityType
{

    FILL,   ///< "FILL"
    ACATC,  ///< "ACATC"
    ACATS,  ///< "ACATS"
    CFEE,   ///< "CFEE"
    CIL,    ///< "CIL"
    CSD,    ///< "CSD"
    CSW,    ///< "CSW"
    DIV,    ///< "DIV"
    DIVCGL, ///< "DIVCGL"
    DIVCGS, ///< "DIVCGS"
    DIVNRA, ///< "DIVNRA"
    DIVROC, ///< "DIVROC"
    DIVTXEX,///< "DIVTXEX"
    DIVWH,  ///< "DIVWH"
    EXTRD,  ///< "EXTRD"
    FEE,    ///< "FEE"
    FXTRD,  ///< "FXTRD"
    INT,    ///< "INT"
    INTPNL, ///< "INTPNL"
    JNLC,   ///< "JNLC"
    JNLS,   ///< "JNLS"
    MA,     ///< "MA"
    MEM,    ///< "MEM"
    NC,     ///< "NC"
    OCT,    ///< "OCT"
    OPASN,  ///< "OPASN"
    OPCSH,  ///< "OPCSH"
    OPEXC,  ///< "OPEXC"
    OPEXP,  ///< "OPEXP"
    OPTRD,  ///< "OPTRD"
    PTC,    ///< "PTC"
    REORG,  ///< "REORG"
    SPIN,   ///< "SPIN"
    SPLIT,  ///< "SPLIT"
    SWP,    ///< "SWP"
    VOF,    ///< "VOF"
    WH      ///< "WH"
};

/**
 * @brief A simple check to see if the ActivityType represents a type that belongs to TradeActivity's.
 *
 *     Currently, the check is just against FILL. However, this might change in the future so we are adding this helper
 *     func here to help ease against future changes.
 *
 *     Returns:
 *         bool: returns true if this ActivityType represents a TradeActivity
 *
 */
constexpr bool is_trade_activity(ActivityType obj)
{
  return (obj==ActivityType::FILL);
}

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::ActivityType obj);
std::string to_str(vp::ActivityType obj);
vp::ActivityType ActivityType_from_str(std::string_view str);
vp::ActivityType ActivityType_from_json(std::string_view str);
bool is_ActivityType(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for ActivityType
template <>
struct glz::meta<vp::ActivityType>
{
  using enum vp::ActivityType;
  static constexpr auto value = glz::enumerate(
    FILL,
    ACATC,
    ACATS,
    CFEE,
    CIL,
    CSD,
    CSW,
    DIV,
    DIVCGL,
    DIVCGS,
    DIVNRA,
    DIVROC,
    DIVTXEX,
    DIVWH,
    EXTRD,
    FEE,
    FXTRD,
    INT,
    INTPNL,
    JNLC,
    JNLS,
    MA,
    MEM,
    NC,
    OCT,
    OPASN,
    OPCSH,
    OPEXC,
    OPEXP,
    OPTRD,
    PTC,
    REORG,
    SPIN,
    SPLIT,
    SWP,
    VOF,
    WH
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "FILL" or "ACATC" for this enum.
 *  @code
 *  std::cout << to_json(vp::ActivityType::FILL);
 *  // "FILL"
 *  @endcode
 */
inline std::string to_json(vp::ActivityType obj)
{
  return glz::write_json(obj).value_or("ActivityType::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns FILL or ACATC for this enum.
 *  @code
 *  std::cout << to_json(vp::ActivityType::FILL);
 *  // FILL
 *  @endcode
 */
inline std::string to_str(vp::ActivityType obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::ActivityType object.
 */
inline vp::ActivityType ActivityType_from_str(std::string_view str)
{
  vp::ActivityType s;
  const std::string json = std::string("\"") + std::string(str) + std::string("\"");
  auto error = glz::read_json(s, json);
  if (error)
  {
    // Check to see if the user passed a json type wrapped in quotes.
    auto error2 = glz::read_json(s, str);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid ActivityType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::ActivityType object.
 */
inline vp::ActivityType ActivityType_from_json(std::string_view str)
{
  vp::ActivityType s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid ActivityType string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'ActivityType'.
 */
inline bool is_ActivityType(std::string_view str)
{
  vp::ActivityType s;

  auto error = glz::read_json(s, str);
  if(!error)
  {
    return true;
  }
  else
  {
    std::string json = std::string("\"") + std::string(str) + std::string("\"");
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return true;
    }
  }
  return false;
}