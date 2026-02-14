#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The exchanges that provide data feeds to Alpaca.
 */
enum class Exchange
{
  Z, ///< Cboe BZ
  I, ///< International Securities Exchange
  M, ///< Chicago Stock Exchange
  U, ///< Members Exchange
  L, ///< Long Term Stock Exchange
  W, ///< CBOE
  X, ///< NASDAQ OMX PSX
  B, ///< NASDAQ OMX BX
  D, ///< FINRA ADF
  J, ///< Cboe EDGA
  P, ///< NYSE Arca
  Q, ///< NASDAQ OMX
  S, ///< NASDAQ Small Cap
  V, ///< IEX
  A, ///< NYSE American (AMEX)
  E, ///< Market Independent
  N, ///< New York Stock Exchange
  T, ///< NASDAQ Int
  Y, ///< Cboe BYX
  C, ///< National Stock Exchange
  H, ///< MIAX
  K  ///< Cboe EDGX
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::Exchange obj);
std::string to_str(vp::Exchange obj);
std::string to_str_long(vp::Exchange obj);

vp::Exchange Exchange_from_str(std::string_view str);
vp::Exchange Exchange_from_json(std::string_view str);
bool is_Exchange(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for Exchange
template <>
struct glz::meta<vp::Exchange>
{
  using enum vp::Exchange;
  static constexpr auto value = glz::enumerate(
    Z,
    I,
    M,
    U,
    L,
    W,
    X,
    B,
    D,
    J,
    P,
    Q,
    S,
    V,
    A,
    E,
    N,
    T,
    Y,
    C,
    H,
    K
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "Z" or "I" for this enum.
 *  @code
 *  std::cout << to_json(vp::Exchange::Z);
 *  // "Z"
 *  @endcode
 */
inline std::string to_json(vp::Exchange obj)
{
  return glz::write_json(obj).value_or("Exchange::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns Z or I for this enum.
 *  @code
 *  std::cout << to_json(vp::Exchange::Z);
 *  // Z
 *  @endcode
 */
inline std::string to_str(vp::Exchange obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Returns the long text representation of the enum:
 *  returns Cboe BZ or International Securities Exchange for this enum.
 *  @code
 *  std::cout << to_str_long(vp::Exchange::Z);
 *  // Cboe BZ
 *  @endcode
 */
inline std::string to_str_long(vp::Exchange obj)
{
  switch (obj) {
    case vp::Exchange::Z:
      return "Cboe BZ";
    case vp::Exchange::I:
      return "International Securities Exchange";
    case vp::Exchange::M:
      return "Chicago Stock Exchange";
    case vp::Exchange::U:
      return "Members Exchange";
    case vp::Exchange::L:
      return "Long Term Stock Exchange";
    case vp::Exchange::W:
      return "CBOE";
    case vp::Exchange::X:
      return "NASDAQ OMX PSX";
    case vp::Exchange::B:
      return "NASDAQ OMX BX";
    case vp::Exchange::D:
      return "FINRA ADF";
    case vp::Exchange::J:
      return "Cboe EDGA";
    case vp::Exchange::P:
      return "NYSE Arca";
    case vp::Exchange::Q:
      return "NASDAQ OMX";
    case vp::Exchange::S:
      return "NASDAQ Small Cap";
    case vp::Exchange::V:
      return "IEX";
    case vp::Exchange::A:
      return "NYSE American (AMEX)";
    case vp::Exchange::E:
      return "Market Independent";
    case vp::Exchange::N:
      return "New York Stock Exchange";
    case vp::Exchange::T:
      return "NASDAQ Int";
    case vp::Exchange::Y:
      return "Cboe BYX";
    case vp::Exchange::C:
      return "National Stock Exchange";
    case vp::Exchange::H:
      return "MIAX";
    case vp::Exchange::K:
      return "Cboe EDGX";
    default:
      return "Unknown Exchange";
  }
}


/**
 * @brief Convert a string_view to a vp::Exchange object.
 */
inline vp::Exchange Exchange_from_str(std::string_view str)
{
  vp::Exchange s;
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
    throw std::invalid_argument("Invalid Exchange string: " + std::string(str));
  }
  return s;
}



/**
 * @brief Convert a string_view to a vp::Exchange object.
 */
inline vp::Exchange Exchange_from_json(std::string_view str)
{
  vp::Exchange s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid Exchange string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'Exchange'.
 */
inline bool is_Exchange(std::string_view str)
{
  vp::Exchange s;

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
