#pragma once



#include <string>
#include <optional>
#include <map>
#include <glaze/glaze.hpp>
#include <iostream>
#include <compare> // Required for std::strong_ordering

namespace vp {


/**
 * @brief Represents a single bar of market data matching the JSON package
 * received from the Alpaca API.
 *
 * @code{json}
 *
 * {
 *    "t": "2022-03-28T17:32:00Z",
 *    "o": 3368.5,
 *    "h": 3376.31,
 *    "l": 3366.76,
 *    "c": 3374.07,
 *    "v": 907.81905184,
 *    "n": 1149,
 *    "vw": 3372.4441210299
 * }
 *
 * @endcode
 *
 */
struct bar_t
{
  std::string t{};          ///< Time "2022-02-01T05:00:00Z"
  double      o=0.0;        ///< Open Price
  double      h=0.0;        ///< High
  double      l=0.0;        ///< Low
  double      c=0.0;        ///< Closeing Price
  uint32_t    v=0;          ///< Volume
  uint32_t    n=0;          ///< Trade Count
  std::optional<double> vw; ///< Volume-weighted average price

  constexpr double      open()const                {return o;}
  constexpr double&     open()                     {return o;}
  constexpr double      high()const                {return h;}
  constexpr double&     high()                     {return h;}
  constexpr double      low()const                 {return l;}
  constexpr double&     low()                      {return l;}
  constexpr double      close()const               {return c;}
  constexpr double&     close()                    {return c;}
  constexpr uint32_t    volume()const              {return v;}
  constexpr uint32_t&   volume()                   {return v;}
  constexpr uint32_t    trade_count()const         {return n;}
  constexpr uint32_t&   trade_count()              {return n;}
  constexpr std::optional<double>  vwap()const     {return vw;}
  constexpr std::optional<double>& vwap()          {return vw;}

  std::string to_json() const;
  static bar_t from_json(const std::string &jsonStr);

  // Three-way comparison operator
  std::strong_ordering operator<=>(const bar_t& other) const = default;

};



/**
 * @brief bar_data_t::to_json
 * @return
 */
inline std::string bar_t::to_json() const
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

inline bar_t bar_t::from_json(const std::string &jsonStr)
{
  bar_t obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error("Failed to parse bar_t JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}


/**
 * @brief The BarSet class
 */
struct BarSet
{
  std::map<std::string, std::vector<bar_t>> bars;

  std::string to_json() const;
};

/**
 * @brief Returns a JSON representation of this class
 */
inline std::string BarSet::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    std::cerr << "error:" << __FUNCTION__ << "json conversion failed with error: " << error;
    return std::string("");
  }
  else
  {
    return json_string;
  }
}

/**
 * @brief The BarResp class
 */
struct BarResp
{
  std::map<std::string, std::vector<bar_t>> bars;
  std::optional<std::string> next_page_token;

  void add(std::string,bar_t bar);
  std::string to_json();
  static BarResp from_json(std::string json_string);
};

inline void BarResp::add(std::string ticker, bar_t bar)
{
  bars[ticker].push_back(bar);
}

inline std::string BarResp::to_json()
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    std::cerr << "error:" << __FUNCTION__ << "json conversion failed with error: " << error;
    return std::string("");
  }
  else
  {
    return json_string;
  }
}

inline BarResp BarResp::from_json(std::string json_string)
{
  BarResp obj;
  auto ec = glz::read_json(obj, json_string);
  if (ec)
  {
    throw std::runtime_error("Failed to parse BarResp JSON: " +
                             std::to_string(static_cast<int>(ec)));
  }
  return obj;
}





} // namespace vp

