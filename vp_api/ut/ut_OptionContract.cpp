#include <gtest/gtest.h>
#include "vp/OptionContract.h"
#include <glaze/glaze.hpp>

TEST(OptionContractTest, DefaultConstruction)
{
  vp::OptionContract contract;

  ASSERT_TRUE(contract.id.empty());
  ASSERT_TRUE(contract.symbol.empty());
  ASSERT_TRUE(contract.name.empty());
  ASSERT_EQ(vp::AssetStatus::active, contract.status);
  ASSERT_FALSE(contract.tradable);
  ASSERT_TRUE(contract.expiration_date.empty());
  ASSERT_FALSE(contract.root_symbol.has_value());
  ASSERT_TRUE(contract.underlying_symbol.empty());
  ASSERT_TRUE(contract.underlying_asset_id.empty());
  ASSERT_EQ(vp::ContractType::call, contract.type);
  ASSERT_EQ(vp::ExerciseStyle::american, contract.style);
  ASSERT_EQ("0", contract.strike_price);
  ASSERT_EQ("100", contract.size);
  ASSERT_FALSE(contract.open_interest.has_value());
  ASSERT_FALSE(contract.open_interest_date.has_value());
  ASSERT_FALSE(contract.close_price.has_value());
  ASSERT_FALSE(contract.close_price_date.has_value());
}

TEST(OptionContractTest, ParameterizedConstructionAndAccessors)
{
  vp::OptionContract contract{
    .id = "opt-uuid-001",
    .symbol = "AAPL250117C00150000",
    .name = "AAPL Jan 17 2025 150 Call",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .expiration_date = "2025-01-17",
    .root_symbol = "AAPL",
    .underlying_symbol = "AAPL",
    .underlying_asset_id = "asset-uuid-aapl",
    .type = vp::ContractType::call,
    .style = vp::ExerciseStyle::american,
    .strike_price = "150.0",
    .size = "100",
    .open_interest = "5432",
    .open_interest_date = "2024-12-20",
    .close_price = "12.50",
    .close_price_date = "2024-12-20"
  };

  ASSERT_EQ("opt-uuid-001", contract.id);
  ASSERT_EQ("AAPL250117C00150000", contract.symbol);
  ASSERT_EQ("AAPL Jan 17 2025 150 Call", contract.name);
  ASSERT_EQ(vp::AssetStatus::active, contract.status);
  ASSERT_TRUE(contract.tradable);
  ASSERT_EQ("2025-01-17", contract.expiration_date);
  ASSERT_EQ("AAPL", contract.root_symbol.value());
  ASSERT_EQ("AAPL", contract.underlying_symbol);
  ASSERT_EQ("asset-uuid-aapl", contract.underlying_asset_id);
  ASSERT_EQ(vp::ContractType::call, contract.type);
  ASSERT_EQ(vp::ExerciseStyle::american, contract.style);
  ASSERT_EQ("150.0", contract.strike_price);
  ASSERT_EQ("100", contract.size);
  ASSERT_EQ("5432", contract.open_interest.value());
  ASSERT_EQ("2024-12-20", contract.open_interest_date.value());
  ASSERT_EQ("12.50", contract.close_price.value());
  ASSERT_EQ("2024-12-20", contract.close_price_date.value());
}

TEST(OptionContractTest, GlazeRoundTrip)
{
  vp::OptionContract original{
    .id = "opt-rt-001",
    .symbol = "MSFT250321P00400000",
    .name = "MSFT Mar 21 2025 400 Put",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .expiration_date = "2025-03-21",
    .root_symbol = "MSFT",
    .underlying_symbol = "MSFT",
    .underlying_asset_id = "asset-uuid-msft",
    .type = vp::ContractType::put,
    .style = vp::ExerciseStyle::american,
    .strike_price = "400.0",
    .size = "100",
    .open_interest = "1234",
    .open_interest_date = "2024-12-19",
    .close_price = "8.75",
    .close_price_date = "2024-12-19"
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::OptionContract deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_EQ(original.id, deserialized.id);
  ASSERT_EQ(original.symbol, deserialized.symbol);
  ASSERT_EQ(original.name, deserialized.name);
  ASSERT_EQ(original.status, deserialized.status);
  ASSERT_EQ(original.tradable, deserialized.tradable);
  ASSERT_EQ(original.expiration_date, deserialized.expiration_date);
  ASSERT_EQ(original.root_symbol, deserialized.root_symbol);
  ASSERT_EQ(original.underlying_symbol, deserialized.underlying_symbol);
  ASSERT_EQ(original.underlying_asset_id, deserialized.underlying_asset_id);
  ASSERT_EQ(original.type, deserialized.type);
  ASSERT_EQ(original.style, deserialized.style);
  ASSERT_EQ(original.strike_price, deserialized.strike_price);
  ASSERT_EQ(original.size, deserialized.size);
  ASSERT_EQ(original.open_interest, deserialized.open_interest);
  ASSERT_EQ(original.open_interest_date, deserialized.open_interest_date);
  ASSERT_EQ(original.close_price, deserialized.close_price);
  ASSERT_EQ(original.close_price_date, deserialized.close_price_date);
}

TEST(OptionContractTest, FromJsonMethod)
{
  std::string json_response = R"({
    "id": "from-json-opt",
    "symbol": "TSLA250620C00250000",
    "name": "TSLA Jun 20 2025 250 Call",
    "status": "active",
    "tradable": true,
    "expiration_date": "2025-06-20",
    "root_symbol": "TSLA",
    "underlying_symbol": "TSLA",
    "underlying_asset_id": "asset-uuid-tsla",
    "type": "call",
    "style": "american",
    "strike_price": "250.0",
    "size": "100",
    "open_interest": "9876",
    "open_interest_date": "2024-12-18",
    "close_price": "22.30",
    "close_price_date": "2024-12-18"
  })";

  vp::OptionContract contract =
    vp::OptionContract::from_json(json_response);

  ASSERT_EQ("from-json-opt", contract.id);
  ASSERT_EQ("TSLA250620C00250000", contract.symbol);
  ASSERT_EQ("TSLA Jun 20 2025 250 Call", contract.name);
  ASSERT_EQ(vp::AssetStatus::active, contract.status);
  ASSERT_TRUE(contract.tradable);
  ASSERT_EQ("2025-06-20", contract.expiration_date);
  ASSERT_EQ("TSLA", contract.root_symbol.value());
  ASSERT_EQ("TSLA", contract.underlying_symbol);
  ASSERT_EQ("asset-uuid-tsla", contract.underlying_asset_id);
  ASSERT_EQ(vp::ContractType::call, contract.type);
  ASSERT_EQ(vp::ExerciseStyle::american, contract.style);
  ASSERT_EQ("250.0", contract.strike_price);
  ASSERT_EQ("100", contract.size);
  ASSERT_EQ("9876", contract.open_interest.value());
  ASSERT_EQ("2024-12-18", contract.open_interest_date.value());
  ASSERT_EQ("22.30", contract.close_price.value());
  ASSERT_EQ("2024-12-18", contract.close_price_date.value());
}

TEST(OptionContractsResponseTest, DefaultConstruction)
{
  vp::OptionContractsResponse response;

  ASSERT_FALSE(response.option_contracts.has_value());
  ASSERT_FALSE(response.next_page_token.has_value());
}

TEST(OptionContractsResponseTest, GlazeRoundTrip)
{
  vp::OptionContract contract{
    .id = "resp-opt-001",
    .symbol = "AAPL250117C00150000",
    .name = "AAPL Jan 17 2025 150 Call",
    .status = vp::AssetStatus::active,
    .tradable = true,
    .expiration_date = "2025-01-17",
    .underlying_symbol = "AAPL",
    .underlying_asset_id = "asset-uuid-aapl",
    .type = vp::ContractType::call,
    .style = vp::ExerciseStyle::american,
    .strike_price = "150.0",
    .size = "100"
  };

  vp::OptionContractsResponse original{
    .option_contracts = std::vector<vp::OptionContract>{contract},
    .next_page_token = "token-abc-123"
  };

  std::string json_str;
  auto error = glz::write_json(original, json_str);
  ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

  vp::OptionContractsResponse deserialized;
  error = glz::read_json(deserialized, json_str);
  ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

  ASSERT_TRUE(deserialized.option_contracts.has_value());
  ASSERT_EQ(1u, deserialized.option_contracts.value().size());
  ASSERT_EQ("resp-opt-001", deserialized.option_contracts.value()[0].id);
  ASSERT_EQ("AAPL250117C00150000", deserialized.option_contracts.value()[0].symbol);
  ASSERT_TRUE(deserialized.next_page_token.has_value());
  ASSERT_EQ("token-abc-123", deserialized.next_page_token.value());
}

TEST(OptionContractsResponseTest, FromJsonMethod)
{
  std::string json_response = R"({
    "option_contracts": [
      {
        "id": "parsed-opt-001",
        "symbol": "GOOG250321P00175000",
        "name": "GOOG Mar 21 2025 175 Put",
        "status": "active",
        "tradable": true,
        "expiration_date": "2025-03-21",
        "underlying_symbol": "GOOG",
        "underlying_asset_id": "asset-uuid-goog",
        "type": "put",
        "style": "american",
        "strike_price": "175.0",
        "size": "100"
      }
    ],
    "next_page_token": "next-page-xyz"
  })";

  vp::OptionContractsResponse response =
    vp::OptionContractsResponse::from_json(json_response);

  ASSERT_TRUE(response.option_contracts.has_value());
  ASSERT_EQ(1u, response.option_contracts.value().size());
  ASSERT_EQ("parsed-opt-001", response.option_contracts.value()[0].id);
  ASSERT_EQ(vp::ContractType::put, response.option_contracts.value()[0].type);
  ASSERT_TRUE(response.next_page_token.has_value());
  ASSERT_EQ("next-page-xyz", response.next_page_token.value());
}
