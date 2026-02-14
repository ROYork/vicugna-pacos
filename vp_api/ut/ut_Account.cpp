#include <gtest/gtest.h>
#include "vp/Account.h"
#include <glaze/glaze.hpp>

TEST(AccountTest, DefaultConstruction)
{
    vp::Account account;

    // Default values should be empty/zero/false
    ASSERT_TRUE(account.id.empty());
    ASSERT_TRUE(account.account_number.empty());
    ASSERT_EQ(0.0, account.buying_power);
    ASSERT_EQ(0.0, account.cash);
    ASSERT_EQ(0.0, account.portfolio_value);
    ASSERT_FALSE(account.pattern_day_trader);
    ASSERT_FALSE(account.trading_blocked);
    ASSERT_FALSE(account.transfers_blocked);
    ASSERT_FALSE(account.account_blocked);
    ASSERT_FALSE(account.trade_suspended_by_user);
    ASSERT_EQ(0, account.multiplier);
    ASSERT_FALSE(account.shorting_enabled);
    ASSERT_EQ(0, account.daytrade_count);
}

TEST(AccountTest, ParameterizedConstructionAndAccessors)
{
    vp::Account account{
        .id = "test-account-123",
        .account_number = "987654321",
        .status = vp::AccountStatus::ACTIVE,
        .currency = "USD",
        .buying_power = 50000.00,
        .regt_buying_power = 50000.00,
        .daytrading_buying_power = 100000.00,
        .non_marginable_buying_power = 50000.00,
        .cash = 25000.00,
        .accrued_fees = 10.50,
        .portfolio_value = 75000.00,
        .pattern_day_trader = false,
        .trading_blocked = false,
        .transfers_blocked = false,
        .account_blocked = false,
        .trade_suspended_by_user = false,
        .multiplier = 2,
        .shorting_enabled = true,
        .equity = 75000.00,
        .last_equity = 74500.00,
        .long_market_value = 50000.00,
        .short_market_value = 0.00,
        .initial_margin = 25000.00,
        .maintenance_margin = 15000.00,
        .last_maintenance_margin = 15000.0,
        .sma = 30000.00,
        .daytrade_count = 2,
        .created_at = "2024-01-15T10:30:00Z"
    };

    ASSERT_EQ("test-account-123", account.id);
    ASSERT_EQ("987654321", account.account_number);
    ASSERT_EQ(vp::AccountStatus::ACTIVE, account.status);
    ASSERT_EQ("USD", account.currency);
    ASSERT_EQ(50000.00, account.buying_power);
    ASSERT_EQ(25000.00, account.cash);
    ASSERT_EQ(75000.00, account.portfolio_value);
    ASSERT_FALSE(account.pattern_day_trader);
    ASSERT_EQ(2, account.multiplier);
    ASSERT_TRUE(account.shorting_enabled);
    ASSERT_EQ(2, account.daytrade_count);
    ASSERT_EQ("2024-01-15T10:30:00Z", account.created_at);
}

TEST(AccountTest, GlazeSerializationDeserialization)
{
    vp::Account original_account{
        .id = "acc-001",
        .account_number = "123456789",
        .status = vp::AccountStatus::ACTIVE,
        .currency = "USD",
        .buying_power = 100000.00,
        .regt_buying_power = 100000.00,
        .daytrading_buying_power = 200000.00,
        .non_marginable_buying_power = 100000.00,
        .cash = 50000.00,
        .accrued_fees = 25.75,
        .portfolio_value = 150000.00,
        .pattern_day_trader = true,
        .trading_blocked = false,
        .transfers_blocked = false,
        .account_blocked = false,
        .trade_suspended_by_user = false,
        .multiplier = 4,
        .shorting_enabled = true,
        .equity = 150000.00,
        .last_equity = 148000.00,
        .long_market_value = 100000.00,
        .short_market_value = 0.00,
        .initial_margin = 50000.00,
        .maintenance_margin = 30000.00,
        .last_maintenance_margin = 29500.0,
        .sma = 60000.00,
        .daytrade_count = 5,
        .created_at = "2023-12-01T08:00:00Z"
    };

    std::string json_str;
    auto error = glz::write_json(original_account, json_str);
    ASSERT_FALSE(error) << "Serialization failed: " << glz::format_error(error, json_str);

    vp::Account deserialized_account;
    error = glz::read_json(deserialized_account, json_str);
    ASSERT_FALSE(error) << "Deserialization failed: " << glz::format_error(error, json_str);

    // Verify all fields match
    ASSERT_EQ(original_account.id, deserialized_account.id);
    ASSERT_EQ(original_account.account_number, deserialized_account.account_number);
    ASSERT_EQ(original_account.status, deserialized_account.status);
    ASSERT_EQ(original_account.currency, deserialized_account.currency);
    ASSERT_EQ(original_account.buying_power, deserialized_account.buying_power);
    ASSERT_EQ(original_account.cash, deserialized_account.cash);
    ASSERT_EQ(original_account.portfolio_value, deserialized_account.portfolio_value);
    ASSERT_EQ(original_account.pattern_day_trader, deserialized_account.pattern_day_trader);
    ASSERT_EQ(original_account.trading_blocked, deserialized_account.trading_blocked);
    ASSERT_EQ(original_account.multiplier, deserialized_account.multiplier);
    ASSERT_EQ(original_account.daytrade_count, deserialized_account.daytrade_count);
    ASSERT_EQ(original_account.created_at, deserialized_account.created_at);
}

TEST(AccountTest, ToJsonMethod)
{
    vp::Account account{
        .id = "test-123",
        .account_number = "987654",
        .status = vp::AccountStatus::ACTIVE,
        .currency = "USD",
        .buying_power = 10000.00,
        .regt_buying_power = 10000.00,
        .daytrading_buying_power = 20000.00,
        .non_marginable_buying_power = 10000.00,
        .cash = 5000.00,
        .accrued_fees = 0.00,
        .portfolio_value = 15000.00,
        .pattern_day_trader = false,
        .trading_blocked = false,
        .transfers_blocked = false,
        .account_blocked = false,
        .trade_suspended_by_user = false,
        .multiplier = 2,
        .shorting_enabled = false,
        .equity = 15000.00,
        .last_equity = 14800.00,
        .long_market_value = 10000.00,
        .short_market_value = 0.00,
        .initial_margin = 5000.00,
        .maintenance_margin = 3000.00,
        .last_maintenance_margin = 2950.0,
        .sma = 6000.00,
        .daytrade_count = 0,
        .created_at = "2024-01-01T00:00:00Z"
    };

    std::string json = account.to_json();

    ASSERT_FALSE(json.empty());
    ASSERT_NE(std::string::npos, json.find("test-123"));
    ASSERT_NE(std::string::npos, json.find("987654"));
    ASSERT_NE(std::string::npos, json.find("ACTIVE"));
    ASSERT_NE(std::string::npos, json.find("USD"));
}

TEST(AccountTest, FromJsonMethod)
{
    std::string json_response = R"({
        "id": "from-json-test",
        "account_number": "111222333",
        "status": "ACTIVE",
        "currency": "USD",
        "buying_power": 75000.50,
        "regt_buying_power": 75000.50,
        "daytrading_buying_power": 150001.00,
        "non_marginable_buying_power": 75000.50,
        "cash": 40000.25,
        "accrued_fees": 15.99,
        "portfolio_value": 115000.75,
        "pattern_day_trader": true,
        "trading_blocked": false,
        "transfers_blocked": false,
        "account_blocked": false,
        "trade_suspended_by_user": false,
        "multiplier": 3,
        "shorting_enabled": true,
        "equity": 115000.75,
        "last_equity": 114000.00,
        "long_market_value": 75000.50,
        "short_market_value": 0.00,
        "initial_margin": 37500.25,
        "maintenance_margin": 22500.15,
        "last_maintenance_margin": 22000.0,
        "sma": 45000.00,
        "daytrade_count": 3,
        "created_at": "2024-06-15T12:30:45Z"
    })";

    vp::Account account = vp::Account::from_json(json_response);

    ASSERT_EQ("from-json-test", account.id);
    ASSERT_EQ("111222333", account.account_number);
    ASSERT_EQ(vp::AccountStatus::ACTIVE, account.status);
    ASSERT_EQ("USD", account.currency);
    ASSERT_DOUBLE_EQ(75000.50, account.buying_power);
    ASSERT_DOUBLE_EQ(40000.25, account.cash);
    ASSERT_DOUBLE_EQ(115000.75, account.portfolio_value);
    ASSERT_TRUE(account.pattern_day_trader);
    ASSERT_FALSE(account.trading_blocked);
    ASSERT_EQ(3, account.multiplier);
    ASSERT_TRUE(account.shorting_enabled);
    ASSERT_EQ(3, account.daytrade_count);
    ASSERT_EQ("2024-06-15T12:30:45Z", account.created_at);
}

TEST(AccountTest, RoundTripSerialization)
{
    // Create original account
    vp::Account original{
        .id = "roundtrip-001",
        .account_number = "555666777",
        .status = vp::AccountStatus::PAPER_ONLY,
        .currency = "USD",
        .buying_power = 25000.00,
        .regt_buying_power = 25000.00,
        .daytrading_buying_power = 50000.00,
        .non_marginable_buying_power = 25000.00,
        .cash = 12500.00,
        .accrued_fees = 5.50,
        .portfolio_value = 37500.00,
        .pattern_day_trader = false,
        .trading_blocked = true,
        .transfers_blocked = false,
        .account_blocked = false,
        .trade_suspended_by_user = false,
        .multiplier = 2,
        .shorting_enabled = false,
        .equity = 37500.00,
        .last_equity = 37000.00,
        .long_market_value = 25000.00,
        .short_market_value = 0.00,
        .initial_margin = 12500.00,
        .maintenance_margin = 7500.00,
        .last_maintenance_margin = 7400.0,
        .sma = 15000.00,
        .daytrade_count = 1,
        .created_at = "2024-03-20T15:45:30Z"
    };

    // Convert to JSON
    std::string json = original.to_json();
    ASSERT_FALSE(json.empty());

    // Parse back from JSON
    vp::Account restored = vp::Account::from_json(json);

    // Verify they're identical
    ASSERT_EQ(original.id, restored.id);
    ASSERT_EQ(original.account_number, restored.account_number);
    ASSERT_EQ(original.status, restored.status);
    ASSERT_EQ(original.buying_power, restored.buying_power);
    ASSERT_EQ(original.cash, restored.cash);
    ASSERT_EQ(original.portfolio_value, restored.portfolio_value);
    ASSERT_EQ(original.pattern_day_trader, restored.pattern_day_trader);
    ASSERT_EQ(original.trading_blocked, restored.trading_blocked);
    ASSERT_EQ(original.daytrade_count, restored.daytrade_count);
    ASSERT_EQ(original.created_at, restored.created_at);
}

TEST(AccountTest, ComparisonOperators)
{
    vp::Account account1{
        .id = "acc-001",
        .account_number = "123456",
        .status = vp::AccountStatus::ACTIVE,
        .currency = "USD",
        .buying_power = 10000.00,
        .regt_buying_power = 10000.00,
        .daytrading_buying_power = 20000.00,
        .non_marginable_buying_power = 10000.00,
        .cash = 5000.00,
        .accrued_fees = 0.00,
        .portfolio_value = 15000.00,
        .pattern_day_trader = false,
        .trading_blocked = false,
        .transfers_blocked = false,
        .account_blocked = false,
        .trade_suspended_by_user = false,
        .multiplier = 2,
        .shorting_enabled = true,
        .equity = 15000.00,
        .last_equity = 14800.00,
        .long_market_value = 10000.00,
        .short_market_value = 0.00,
        .initial_margin = 5000.00,
        .maintenance_margin = 3000.00,
        .last_maintenance_margin = 2950.0,
        .sma = 6000.00,
        .daytrade_count = 0,
        .created_at = "2024-01-01T00:00:00Z"
    };

    vp::Account account2 = account1;  // Copy

    // Test equality
    ASSERT_EQ(account1, account2);
    ASSERT_TRUE(account1 == account2);
    ASSERT_FALSE(account1 != account2);

    // Modify one field
    account2.cash = 6000.00;
    ASSERT_NE(account1, account2);
    ASSERT_FALSE(account1 == account2);
    ASSERT_TRUE(account1 != account2);
}

TEST(AccountTest, BlockedAccountFlags)
{
    vp::Account blocked_account{
        .id = "blocked-001",
        .account_number = "999888777",
        .status = vp::AccountStatus::DISABLED,
        .currency = "USD",
        .buying_power = 0.00,
        .regt_buying_power = 0.00,
        .daytrading_buying_power = 0.00,
        .non_marginable_buying_power = 0.00,
        .cash = 1000.00,
        .accrued_fees = 0.00,
        .portfolio_value = 1000.00,
        .pattern_day_trader = true,
        .trading_blocked = true,
        .transfers_blocked = true,
        .account_blocked = true,
        .trade_suspended_by_user = true,
        .multiplier = 0,
        .shorting_enabled = false,
        .equity = 1000.00,
        .last_equity = 1000.00,
        .long_market_value = 0.00,
        .short_market_value = 0.00,
        .initial_margin = 0.00,
        .maintenance_margin = 0.00,
        .last_maintenance_margin = 0.0,
        .sma = 0.00,
        .daytrade_count = 10,
        .created_at = "2023-01-01T00:00:00Z"
    };

    ASSERT_TRUE(blocked_account.pattern_day_trader);
    ASSERT_TRUE(blocked_account.trading_blocked);
    ASSERT_TRUE(blocked_account.transfers_blocked);
    ASSERT_TRUE(blocked_account.account_blocked);
    ASSERT_TRUE(blocked_account.trade_suspended_by_user);
    ASSERT_EQ(vp::AccountStatus::DISABLED, blocked_account.status);

    // Serialize and deserialize
    std::string json = blocked_account.to_json();
    vp::Account restored = vp::Account::from_json(json);

    ASSERT_TRUE(restored.pattern_day_trader);
    ASSERT_TRUE(restored.trading_blocked);
    ASSERT_TRUE(restored.transfers_blocked);
    ASSERT_TRUE(restored.account_blocked);
    ASSERT_TRUE(restored.trade_suspended_by_user);
}

TEST(AccountTest, VariousAccountStatuses)
{
    std::vector<vp::AccountStatus> statuses = {
        vp::AccountStatus::ACTIVE,
        vp::AccountStatus::PAPER_ONLY,
        vp::AccountStatus::APPROVAL_PENDING,
        vp::AccountStatus::DISABLED,
        vp::AccountStatus::REJECTED
    };

    for (const auto& status : statuses) {
        vp::Account account{
            .id = "test-status",
            .account_number = "000000000",
            .status = status,
            .currency = "USD",
            .buying_power = 1000.00,
            .regt_buying_power = 1000.00,
            .daytrading_buying_power = 2000.00,
            .non_marginable_buying_power = 1000.00,
            .cash = 500.00,
            .accrued_fees = 0.00,
            .portfolio_value = 1500.00,
            .pattern_day_trader = false,
            .trading_blocked = false,
            .transfers_blocked = false,
            .account_blocked = false,
            .trade_suspended_by_user = false,
            .multiplier = 2,
            .shorting_enabled = true,
            .equity = 1500.00,
            .last_equity = 1450.00,
            .long_market_value = 1000.00,
            .short_market_value = 0.00,
            .initial_margin = 500.00,
            .maintenance_margin = 300.00,
            .last_maintenance_margin = 290.0,
            .sma = 600.00,
            .daytrade_count = 0,
            .created_at = "2024-01-01T00:00:00Z"
        };

        std::string json = account.to_json();
        vp::Account restored = vp::Account::from_json(json);

        ASSERT_EQ(status, restored.status);
    }
}
