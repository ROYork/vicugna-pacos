#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief Represents the current exchanges Alpaca supports.
 */
enum class AssetExchange
{
  AMEX,   ///< "AMEX"
  ARCA,   ///< "ARCA"
  BATS,   ///< "BATS"
  NYSE,   ///< "NYSE"
  NASDAQ, ///< "NASDAQ"
  NYSEARCA, ///< "NYSEARCA"
  FTXU,   ///< "FTXU"
  CBSE,   ///< "CBSE"
  GNSS,   ///< "GNSS"
  ERSX,   ///< "ERSX"
  OTC,    ///< "OTC"
  CRYPTO, ///< "CRYPTO"
  EMPTY   ///< ""
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::AssetExchange obj);
std::string to_str(vp::AssetExchange obj);
vp::AssetExchange AssetExchange_from_str(std::string_view str);
vp::AssetExchange AssetExchange_from_json(std::string_view str);
bool is_AssetExchange(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for AssetExchange
template <>
struct glz::meta<vp::AssetExchange>
{
  using enum vp::AssetExchange;
  static constexpr auto value = glz::enumerate(
    AMEX,
    ARCA,
    BATS,
    NYSE,
    NASDAQ,
    NYSEARCA,
    FTXU,
    CBSE,
    GNSS,
    ERSX,
    OTC,
    CRYPTO,
    EMPTY
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "AMEX" or "ARCA" for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetExchange::AMEX);
 *  // "AMEX"
 *  @endcode
 */
inline std::string to_json(vp::AssetExchange obj)
{
  return glz::write_json(obj).value_or("AssetExchange::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns AMEX or ARCA for this enum.
 *  @code
 *  std::cout << to_json(vp::AssetExchange::AMEX);
 *  // AMEX
 *  @endcode
 */
inline std::string to_str(vp::AssetExchange obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::AssetExchange object.
 */
inline vp::AssetExchange AssetExchange_from_str(std::string_view str)
{
  vp::AssetExchange s;
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
    throw std::invalid_argument("Invalid AssetExchange string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::AssetExchange object.
 */
inline vp::AssetExchange AssetExchange_from_json(std::string_view str)
{
  vp::AssetExchange s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid AssetExchange string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'AssetExchange'.
 */
inline bool is_AssetExchange(std::string_view str)
{
  vp::AssetExchange s;

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