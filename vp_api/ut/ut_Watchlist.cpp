#include <gtest/gtest.h>
#include "vp/Watchlist.h"
#include <glaze/glaze.hpp>

TEST(WatchlistTest, DefaultConstruction)
{
  vp::Watchlist watchlist;

  ASSERT_TRUE(watchlist.id.empty());
  ASSERT_TRUE(watchlist.account_id.empty());
  ASSERT_TRUE(watchlist.name.empty());
  ASSERT_TRUE(watchlist.created_at.empty());
  ASSERT_TRUE(watchlist.updated_at.empty());
  ASSERT_FALSE(watchlist.assets.has_value());
}

TEST(WatchlistTest, ParameterizedConstructionAndAccessors)
{
  vp::Asset asset1{
    .id = "asset-001",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NASDAQ,
    .symbol = "AAPL",
    .name = "Apple Inc.",
    .status = vp::AssetStatus::active,
    .tradable = true
  };

  vp::Asset asset2{
    .id = "asset-002",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NASDAQ,
    .symbol = "GOOG",
    .name = "Alphabet Inc.",
    .status = vp::AssetStatus::active,
    .tradable = true
  };

  vp::Watchlist watchlist{
    .id = "watchlist-uuid-001",
    .account_id = "account-uuid-001",
    .name = "My Tech Stocks",
    .created_at = "2024-01-15T10:30:00Z",
    .updated_at = "2024-01-16T14:00:00Z",
    .assets = std::vector<vp::Asset>{asset1, asset2}
  };

  ASSERT_EQ("watchlist-uuid-001", watchlist.id);
  ASSERT_EQ("account-uuid-001", watchlist.account_id);
  ASSERT_EQ("My Tech Stocks", watchlist.name);
  ASSERT_EQ("2024-01-15T10:30:00Z", watchlist.created_at);
  ASSERT_EQ("2024-01-16T14:00:00Z", watchlist.updated_at);
  ASSERT_TRUE(watchlist.assets.has_value());
  ASSERT_EQ(2u, watchlist.assets.value().size());
  ASSERT_EQ("AAPL", watchlist.assets.value()[0].symbol);
  ASSERT_EQ("GOOG", watchlist.assets.value()[1].symbol);
}

TEST(WatchlistTest, GlazeRoundTrip)
{
  vp::Asset asset{
    .id = "asset-rt-001",
    .asset_class = vp::AssetClass::us_equity,
    .exchange = vp::AssetExchange::NYSE,
    .symbol = "MSFT",
    .name = "Microsoft Corporation",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .marginable = true,
    .shortable = true,
    .easy_to_borrow = true,
    .fractionable = true
  };

  vp::Watchlist original{
    .id = "wl-rt-001",
    .account_id = "acc-rt-001",
    .name = "Round Trip Watchlist",
    .created_at = "2024-03-01T08:00:00Z",
    .updated_at = "2024-03-02T09:00:00Z",
    .assets = std::vector<vp::Asset>{asset}
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::Watchlist deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.id, deserialized.id);
  ASSERT_EQ(original.account_id, deserialized.account_id);
  ASSERT_EQ(original.name, deserialized.name);
  ASSERT_EQ(original.created_at, deserialized.created_at);
  ASSERT_EQ(original.updated_at, deserialized.updated_at);
  ASSERT_TRUE(deserialized.assets.has_value());
  ASSERT_EQ(1u, deserialized.assets.value().size());
  ASSERT_EQ("MSFT", deserialized.assets.value()[0].symbol);
}

TEST(WatchlistTest, FromJsonMethod)
{
  std::string json_response = R"({
    "id": "from-json-wl",
    "account_id": "from-json-acc",
    "name": "Parsed Watchlist",
    "created_at": "2024-06-01T12:00:00Z",
    "updated_at": "2024-06-02T13:00:00Z",
    "assets": [
      {
        "id": "parsed-asset-001",
        "class": "us_equity",
        "exchange": "NASDAQ",
        "symbol": "TSLA",
        "name": "Tesla Inc.",
        "status": "active",
        "tradable": true,
        "marginable": true,
        "shortable": false,
        "easy_to_borrow": false,
        "fractionable": true
      }
    ]
  })";

  vp::Watchlist watchlist = vp::Watchlist::from_json(json_response);

  ASSERT_EQ("from-json-wl", watchlist.id);
  ASSERT_EQ("from-json-acc", watchlist.account_id);
  ASSERT_EQ("Parsed Watchlist", watchlist.name);
  ASSERT_EQ("2024-06-01T12:00:00Z", watchlist.created_at);
  ASSERT_EQ("2024-06-02T13:00:00Z", watchlist.updated_at);
  ASSERT_TRUE(watchlist.assets.has_value());
  ASSERT_EQ(1u, watchlist.assets.value().size());
  ASSERT_EQ("TSLA", watchlist.assets.value()[0].symbol);
  ASSERT_EQ("Tesla Inc.", watchlist.assets.value()[0].name);
  ASSERT_TRUE(watchlist.assets.value()[0].tradable);
}

TEST(WatchlistTest, ComparisonOperators)
{
  vp::Watchlist wl1{
    .id = "wl-cmp-001",
    .account_id = "acc-cmp-001",
    .name = "Comparison Watchlist",
    .created_at = "2024-01-01T00:00:00Z",
    .updated_at = "2024-01-01T00:00:00Z"
  };

  vp::Watchlist wl2 = wl1;  // Copy

  // Test equality
  ASSERT_EQ(wl1, wl2);
  ASSERT_TRUE(wl1 == wl2);
  ASSERT_FALSE(wl1 != wl2);

  // Modify one field
  wl2.name = "Different Name";
  ASSERT_NE(wl1, wl2);
  ASSERT_FALSE(wl1 == wl2);
  ASSERT_TRUE(wl1 != wl2);
}
