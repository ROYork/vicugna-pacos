#include <gtest/gtest.h>
#include "vp/AccountConfiguration.h"
#include <glaze/glaze.hpp>

TEST(AccountConfigurationTest, DefaultConstruction)
{
  vp::AccountConfiguration config;

  ASSERT_EQ(vp::DTBPCheck::both, config.dtbp_check);
  ASSERT_TRUE(config.fractional_trading);
  ASSERT_EQ("4", config.max_margin_multiplier);
  ASSERT_FALSE(config.no_shorting);
  ASSERT_EQ(vp::PDTCheck::both, config.pdt_check);
  ASSERT_FALSE(config.suspend_trade);
  ASSERT_EQ(vp::TradeConfirmationEmail::all, config.trade_confirm_email);
  ASSERT_FALSE(config.ptp_no_exception_entry);
  ASSERT_FALSE(config.max_options_trading_level.has_value());
}

TEST(AccountConfigurationTest, ParameterizedConstructionAndAccessors)
{
  vp::AccountConfiguration config{
    .dtbp_check = vp::DTBPCheck::entry,
    .fractional_trading = false,
    .max_margin_multiplier = "2",
    .no_shorting = true,
    .pdt_check = vp::PDTCheck::exit,
    .suspend_trade = true,
    .trade_confirm_email = vp::TradeConfirmationEmail::none,
    .ptp_no_exception_entry = true,
    .max_options_trading_level = 3
  };

  ASSERT_EQ(vp::DTBPCheck::entry, config.dtbp_check);
  ASSERT_FALSE(config.fractional_trading);
  ASSERT_EQ("2", config.max_margin_multiplier);
  ASSERT_TRUE(config.no_shorting);
  ASSERT_EQ(vp::PDTCheck::exit, config.pdt_check);
  ASSERT_TRUE(config.suspend_trade);
  ASSERT_EQ(vp::TradeConfirmationEmail::none, config.trade_confirm_email);
  ASSERT_TRUE(config.ptp_no_exception_entry);
  ASSERT_TRUE(config.max_options_trading_level.has_value());
  ASSERT_EQ(3, config.max_options_trading_level.value());
}

TEST(AccountConfigurationTest, GlazeRoundTrip)
{
  vp::AccountConfiguration original{
    .dtbp_check = vp::DTBPCheck::exit,
    .fractional_trading = true,
    .max_margin_multiplier = "1",
    .no_shorting = false,
    .pdt_check = vp::PDTCheck::entry,
    .suspend_trade = false,
    .trade_confirm_email = vp::TradeConfirmationEmail::all,
    .ptp_no_exception_entry = false,
    .max_options_trading_level = 2
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::AccountConfiguration deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.dtbp_check, deserialized.dtbp_check);
  ASSERT_EQ(original.fractional_trading, deserialized.fractional_trading);
  ASSERT_EQ(original.max_margin_multiplier, deserialized.max_margin_multiplier);
  ASSERT_EQ(original.no_shorting, deserialized.no_shorting);
  ASSERT_EQ(original.pdt_check, deserialized.pdt_check);
  ASSERT_EQ(original.suspend_trade, deserialized.suspend_trade);
  ASSERT_EQ(original.trade_confirm_email, deserialized.trade_confirm_email);
  ASSERT_EQ(original.ptp_no_exception_entry, deserialized.ptp_no_exception_entry);
  ASSERT_EQ(original.max_options_trading_level, deserialized.max_options_trading_level);
}

TEST(AccountConfigurationTest, FromJsonMethod)
{
  std::string json_response = R"({
    "dtbp_check": "both",
    "fractional_trading": true,
    "max_margin_multiplier": "4",
    "no_shorting": false,
    "pdt_check": "both",
    "suspend_trade": false,
    "trade_confirm_email": "all",
    "ptp_no_exception_entry": false,
    "max_options_trading_level": 1
  })";

  vp::AccountConfiguration config =
    vp::AccountConfiguration::from_json(json_response);

  ASSERT_EQ(vp::DTBPCheck::both, config.dtbp_check);
  ASSERT_TRUE(config.fractional_trading);
  ASSERT_EQ("4", config.max_margin_multiplier);
  ASSERT_FALSE(config.no_shorting);
  ASSERT_EQ(vp::PDTCheck::both, config.pdt_check);
  ASSERT_FALSE(config.suspend_trade);
  ASSERT_EQ(vp::TradeConfirmationEmail::all, config.trade_confirm_email);
  ASSERT_FALSE(config.ptp_no_exception_entry);
  ASSERT_TRUE(config.max_options_trading_level.has_value());
  ASSERT_EQ(1, config.max_options_trading_level.value());
}

TEST(AccountConfigurationTest, ComparisonOperators)
{
  vp::AccountConfiguration config1{
    .dtbp_check = vp::DTBPCheck::both,
    .fractional_trading = true,
    .max_margin_multiplier = "4",
    .no_shorting = false,
    .pdt_check = vp::PDTCheck::both,
    .suspend_trade = false,
    .trade_confirm_email = vp::TradeConfirmationEmail::all,
    .ptp_no_exception_entry = false
  };

  vp::AccountConfiguration config2 = config1;  // Copy

  // Test equality
  ASSERT_EQ(config1, config2);
  ASSERT_TRUE(config1 == config2);
  ASSERT_FALSE(config1 != config2);

  // Modify one field
  config2.max_margin_multiplier = "2";
  ASSERT_NE(config1, config2);
  ASSERT_FALSE(config1 == config2);
  ASSERT_TRUE(config1 != config2);
}
