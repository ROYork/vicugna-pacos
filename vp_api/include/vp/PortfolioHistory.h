#pragma once
#include <glaze/glaze.hpp>
#include <string>
#include <optional>
#include <vector>
#include <compare>
#include <cstdint>

namespace vp {

/**
 * @brief Represents portfolio history data
 *
 * See https://alpaca.markets/docs/api-references/trading-api/portfolio-history/
 */
struct PortfolioHistory
{
  std::vector<int64_t> timestamp;
  std::vector<std::optional<double>> equity;
  std::vector<std::optional<double>> profit_loss;
  std::vector<std::optional<double>> profit_loss_pct;
  double base_value = 0.0;
  std::string timeframe = "";

  std::string to_json() const;
  static PortfolioHistory from_json(const std::string& jsonStr);

  auto operator<=>(const PortfolioHistory& other) const = default;
};

} // namespace vp

template <>
struct glz::meta<vp::PortfolioHistory>
{
  using T = vp::PortfolioHistory;
  static constexpr auto value = glz::object(
    "timestamp", &T::timestamp,
    "equity", &T::equity,
    "profit_loss", &T::profit_loss,
    "profit_loss_pct", &T::profit_loss_pct,
    "base_value", &T::base_value,
    "timeframe", &T::timeframe
  );
};

inline std::string vp::PortfolioHistory::to_json() const
{
  std::string json_string{};
  auto error = glz::write_json(*this, json_string);
  if (error)
  {
    return std::string("");
  }
  return json_string;
}

inline vp::PortfolioHistory vp::PortfolioHistory::from_json(
  const std::string& jsonStr)
{
  vp::PortfolioHistory obj;
  auto ec = glz::read_json(obj, jsonStr);
  if (ec)
  {
    throw std::runtime_error(
      "Failed to parse PortfolioHistory JSON: " +
      std::to_string(static_cast<int>(ec)));
  }
  return obj;
}
