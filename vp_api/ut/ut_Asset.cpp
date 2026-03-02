#include <gtest/gtest.h>
#include "vp/Asset.h"
#include <glaze/glaze.hpp>

TEST(AssetTest, DefaultConstruction)
{
  vp::Asset asset;

  ASSERT_TRUE(asset.id.empty());
  ASSERT_EQ(vp::AssetClass::us_equity, asset.asset_class);
  ASSERT_EQ(vp::AssetExchange::EMPTY, asset.exchange);
  ASSERT_TRUE(asset.symbol.empty());
  ASSERT_TRUE(asset.name.empty());
  ASSERT_EQ(vp::AssetStatus::active, asset.status);
  ASSERT_FALSE(asset.tradable);
  ASSERT_FALSE(asset.marginable);
  ASSERT_FALSE(asset.shortable);
  ASSERT_FALSE(asset.easy_to_borrow);
  ASSERT_FALSE(asset.fractionable);
  ASSERT_FALSE(asset.min_order_size.has_value());
  ASSERT_FALSE(asset.min_trade_increment.has_value());
  ASSERT_FALSE(asset.price_increment.has_value());
  ASSERT_FALSE(asset.maintenance_margin_requirement.has_value());
  ASSERT_FALSE(asset.attributes.has_value());
}

TEST(AssetTest, ParameterizedConstructionAndAccessors)
{
  vp::Asset asset{
    .id = "asset-uuid-001",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NASDAQ,
    .symbol = "AAPL",
    .name = "Apple Inc.",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .marginable = true,
    .shortable = true,
    .easy_to_borrow = true,
    .fractionable = true,
    .min_order_size = "1",
    .min_trade_increment = "0.0001",
    .price_increment = "0.01",
    .maintenance_margin_requirement = "30",
    .attributes = std::vector<std::string>{"ptp_no_exception"}
  };

  ASSERT_EQ("asset-uuid-001", asset.id);
  ASSERT_EQ(vp::AssetClass::us_equity, asset.asset_class);
  ASSERT_EQ(vp::AssetExchange::NASDAQ, asset.exchange);
  ASSERT_EQ("AAPL", asset.symbol);
  ASSERT_EQ("Apple Inc.", asset.name);
  ASSERT_EQ(vp::AssetStatus::active, asset.status);
  ASSERT_TRUE(asset.tradable);
  ASSERT_TRUE(asset.marginable);
  ASSERT_TRUE(asset.shortable);
  ASSERT_TRUE(asset.easy_to_borrow);
  ASSERT_TRUE(asset.fractionable);
  ASSERT_EQ("1", asset.min_order_size.value());
  ASSERT_EQ("0.0001", asset.min_trade_increment.value());
  ASSERT_EQ("0.01", asset.price_increment.value());
  ASSERT_EQ("30", asset.maintenance_margin_requirement.value());
  ASSERT_TRUE(asset.attributes.has_value());
  ASSERT_EQ(1u, asset.attributes.value().size());
  ASSERT_EQ("ptp_no_exception", asset.attributes.value()[0]);
}

TEST(AssetTest, GlazeSerializationDeserialization)
{
  vp::Asset original{
    .id = "ser-asset-001",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NYSE,
    .symbol = "MSFT",
    .name = "Microsoft Corporation",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .marginable = true,
    .shortable = false,
    .easy_to_borrow = false,
    .fractionable = true,
    .min_order_size = "1",
    .min_trade_increment = "0.001",
    .price_increment = "0.01"
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::Asset deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.id, deserialized.id);
  ASSERT_EQ(original.asset_class, deserialized.asset_class);
  ASSERT_EQ(original.exchange, deserialized.exchange);
  ASSERT_EQ(original.symbol, deserialized.symbol);
  ASSERT_EQ(original.name, deserialized.name);
  ASSERT_EQ(original.status, deserialized.status);
  ASSERT_EQ(original.tradable, deserialized.tradable);
  ASSERT_EQ(original.marginable, deserialized.marginable);
  ASSERT_EQ(original.shortable, deserialized.shortable);
  ASSERT_EQ(original.easy_to_borrow, deserialized.easy_to_borrow);
  ASSERT_EQ(original.fractionable, deserialized.fractionable);
  ASSERT_EQ(original.min_order_size, deserialized.min_order_size);
  ASSERT_EQ(original.min_trade_increment, deserialized.min_trade_increment);
  ASSERT_EQ(original.price_increment, deserialized.price_increment);
}

TEST(AssetTest, FromJsonMethod)
{
  // Note: the JSON key is "class" not "asset_class" per glz::meta mapping
  std::string json_response = R"({
    "id": "from-json-asset",
    "class": "us_equity",
    "exchange": "NASDAQ",
    "symbol": "GOOG",
    "name": "Alphabet Inc.",
    "status": "active",
    "tradable": true,
    "marginable": true,
    "shortable": true,
    "easy_to_borrow": true,
    "fractionable": false,
    "min_order_size": "1",
    "min_trade_increment": "0.0001",
    "price_increment": "0.01"
  })";

  vp::Asset asset = vp::Asset::from_json(json_response);

  ASSERT_EQ("from-json-asset", asset.id);
  ASSERT_EQ(vp::AssetClass::us_equity, asset.asset_class);
  ASSERT_EQ(vp::AssetExchange::NASDAQ, asset.exchange);
  ASSERT_EQ("GOOG", asset.symbol);
  ASSERT_EQ("Alphabet Inc.", asset.name);
  ASSERT_EQ(vp::AssetStatus::active, asset.status);
  ASSERT_TRUE(asset.tradable);
  ASSERT_TRUE(asset.marginable);
  ASSERT_TRUE(asset.shortable);
  ASSERT_TRUE(asset.easy_to_borrow);
  ASSERT_FALSE(asset.fractionable);
  ASSERT_EQ("1", asset.min_order_size.value());
  ASSERT_EQ("0.0001", asset.min_trade_increment.value());
  ASSERT_EQ("0.01", asset.price_increment.value());
}

TEST(AssetTest, ComparisonOperators)
{
  vp::Asset asset1{
    .id = "cmp-asset-001",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NYSE,
    .symbol = "AAPL",
    .name = "Apple Inc.",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .marginable = true,
    .shortable = true,
    .easy_to_borrow = true,
    .fractionable = true
  };

  vp::Asset asset2 = asset1;  // Copy

  // Test equality
  ASSERT_EQ(asset1, asset2);
  ASSERT_TRUE(asset1 == asset2);
  ASSERT_FALSE(asset1 != asset2);

  // Modify one field
  asset2.symbol = "MSFT";
  ASSERT_NE(asset1, asset2);
  ASSERT_FALSE(asset1 == asset2);
  ASSERT_TRUE(asset1 != asset2);
}
