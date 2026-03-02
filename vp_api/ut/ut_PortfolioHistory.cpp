#include <gtest/gtest.h>
#include "vp/PortfolioHistory.h"
#include <glaze/glaze.hpp>

TEST(PortfolioHistoryTest, DefaultConstruction)
{
  vp::PortfolioHistory history;

  ASSERT_TRUE(history.timestamp.empty());
  ASSERT_TRUE(history.equity.empty());
  ASSERT_TRUE(history.profit_loss.empty());
  ASSERT_TRUE(history.profit_loss_pct.empty());
  ASSERT_DOUBLE_EQ(0.0, history.base_value);
  ASSERT_TRUE(history.timeframe.empty());
}

TEST(PortfolioHistoryTest, ParameterizedConstructionAndAccessors)
{
  vp::PortfolioHistory history{
    .timestamp = {1704067200, 1704153600, 1704240000},
    .equity = {100000.0, 101500.0, 99800.0},
    .profit_loss = {0.0, 1500.0, -200.0},
    .profit_loss_pct = {0.0, 0.015, -0.002},
    .base_value = 100000.0,
    .timeframe = "1D"
  };

  ASSERT_EQ(3u, history.timestamp.size());
  ASSERT_EQ(1704067200, history.timestamp[0]);
  ASSERT_EQ(1704153600, history.timestamp[1]);
  ASSERT_EQ(1704240000, history.timestamp[2]);

  ASSERT_EQ(3u, history.equity.size());
  ASSERT_TRUE(history.equity[0].has_value());
  ASSERT_DOUBLE_EQ(100000.0, history.equity[0].value());
  ASSERT_DOUBLE_EQ(101500.0, history.equity[1].value());
  ASSERT_DOUBLE_EQ(99800.0, history.equity[2].value());

  ASSERT_EQ(3u, history.profit_loss.size());
  ASSERT_DOUBLE_EQ(0.0, history.profit_loss[0].value());
  ASSERT_DOUBLE_EQ(1500.0, history.profit_loss[1].value());
  ASSERT_DOUBLE_EQ(-200.0, history.profit_loss[2].value());

  ASSERT_EQ(3u, history.profit_loss_pct.size());
  ASSERT_DOUBLE_EQ(0.0, history.profit_loss_pct[0].value());
  ASSERT_DOUBLE_EQ(0.015, history.profit_loss_pct[1].value());
  ASSERT_DOUBLE_EQ(-0.002, history.profit_loss_pct[2].value());

  ASSERT_DOUBLE_EQ(100000.0, history.base_value);
  ASSERT_EQ("1D", history.timeframe);
}

TEST(PortfolioHistoryTest, GlazeRoundTrip)
{
  vp::PortfolioHistory original{
    .timestamp = {1700000000, 1700086400},
    .equity = {50000.0, 50500.0},
    .profit_loss = {0.0, 500.0},
    .profit_loss_pct = {0.0, 0.01},
    .base_value = 50000.0,
    .timeframe = "1H"
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::PortfolioHistory deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.timestamp.size(), deserialized.timestamp.size());
  for (size_t i = 0; i < original.timestamp.size(); ++i)
  {
    ASSERT_EQ(original.timestamp[i], deserialized.timestamp[i]);
  }

  ASSERT_EQ(original.equity.size(), deserialized.equity.size());
  for (size_t i = 0; i < original.equity.size(); ++i)
  {
    ASSERT_EQ(original.equity[i], deserialized.equity[i]);
  }

  ASSERT_EQ(original.profit_loss.size(), deserialized.profit_loss.size());
  for (size_t i = 0; i < original.profit_loss.size(); ++i)
  {
    ASSERT_EQ(original.profit_loss[i], deserialized.profit_loss[i]);
  }

  ASSERT_EQ(original.profit_loss_pct.size(), deserialized.profit_loss_pct.size());
  for (size_t i = 0; i < original.profit_loss_pct.size(); ++i)
  {
    ASSERT_EQ(original.profit_loss_pct[i], deserialized.profit_loss_pct[i]);
  }

  ASSERT_DOUBLE_EQ(original.base_value, deserialized.base_value);
  ASSERT_EQ(original.timeframe, deserialized.timeframe);
}

TEST(PortfolioHistoryTest, FromJsonMethod)
{
  std::string json_response = R"({
    "timestamp": [1704067200, 1704153600],
    "equity": [75000.50, 76200.25],
    "profit_loss": [0.0, 1199.75],
    "profit_loss_pct": [0.0, 0.016],
    "base_value": 75000.50,
    "timeframe": "1D"
  })";

  vp::PortfolioHistory history =
    vp::PortfolioHistory::from_json(json_response);

  ASSERT_EQ(2u, history.timestamp.size());
  ASSERT_EQ(1704067200, history.timestamp[0]);
  ASSERT_EQ(1704153600, history.timestamp[1]);

  ASSERT_EQ(2u, history.equity.size());
  ASSERT_DOUBLE_EQ(75000.50, history.equity[0].value());
  ASSERT_DOUBLE_EQ(76200.25, history.equity[1].value());

  ASSERT_EQ(2u, history.profit_loss.size());
  ASSERT_DOUBLE_EQ(0.0, history.profit_loss[0].value());
  ASSERT_DOUBLE_EQ(1199.75, history.profit_loss[1].value());

  ASSERT_EQ(2u, history.profit_loss_pct.size());
  ASSERT_DOUBLE_EQ(0.0, history.profit_loss_pct[0].value());
  ASSERT_DOUBLE_EQ(0.016, history.profit_loss_pct[1].value());

  ASSERT_DOUBLE_EQ(75000.50, history.base_value);
  ASSERT_EQ("1D", history.timeframe);
}
