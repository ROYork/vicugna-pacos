#include <gtest/gtest.h>
#include "vp/AssetExchange.h"

TEST(AssetExchangeTest, ToString) {
    ASSERT_EQ("AMEX", to_str(vp::AssetExchange::AMEX));
    ASSERT_EQ("ARCA", to_str(vp::AssetExchange::ARCA));
    ASSERT_EQ("BATS", to_str(vp::AssetExchange::BATS));
    ASSERT_EQ("NYSE", to_str(vp::AssetExchange::NYSE));
    ASSERT_EQ("NASDAQ", to_str(vp::AssetExchange::NASDAQ));
    ASSERT_EQ("NYSEARCA", to_str(vp::AssetExchange::NYSEARCA));
    ASSERT_EQ("FTXU", to_str(vp::AssetExchange::FTXU));
    ASSERT_EQ("CBSE", to_str(vp::AssetExchange::CBSE));
    ASSERT_EQ("GNSS", to_str(vp::AssetExchange::GNSS));
    ASSERT_EQ("ERSX", to_str(vp::AssetExchange::ERSX));
    ASSERT_EQ("OTC", to_str(vp::AssetExchange::OTC));
    ASSERT_EQ("CRYPTO", to_str(vp::AssetExchange::CRYPTO));
    ASSERT_EQ("EMPTY", to_str(vp::AssetExchange::EMPTY));
}

TEST(AssetExchangeTest, FromString) {
    ASSERT_EQ(vp::AssetExchange::AMEX,     AssetExchange_from_str("AMEX"));
    ASSERT_EQ(vp::AssetExchange::ARCA,     AssetExchange_from_str("ARCA"));
    ASSERT_EQ(vp::AssetExchange::BATS,     AssetExchange_from_str("BATS"));
    ASSERT_EQ(vp::AssetExchange::NYSE,     AssetExchange_from_str("NYSE"));
    ASSERT_EQ(vp::AssetExchange::NASDAQ,   AssetExchange_from_str("NASDAQ"));
    ASSERT_EQ(vp::AssetExchange::NYSEARCA, AssetExchange_from_str("NYSEARCA"));
    ASSERT_EQ(vp::AssetExchange::FTXU,     AssetExchange_from_str("FTXU"));
    ASSERT_EQ(vp::AssetExchange::CBSE,     AssetExchange_from_str("CBSE"));
    ASSERT_EQ(vp::AssetExchange::GNSS,     AssetExchange_from_str("GNSS"));
    ASSERT_EQ(vp::AssetExchange::ERSX,     AssetExchange_from_str("ERSX"));
    ASSERT_EQ(vp::AssetExchange::OTC,      AssetExchange_from_str("OTC"));
    ASSERT_EQ(vp::AssetExchange::CRYPTO,   AssetExchange_from_str("CRYPTO"));
    ASSERT_EQ(vp::AssetExchange::EMPTY,    AssetExchange_from_str("EMPTY"));
}

TEST(AssetExchangeTest, FromStringInvalid) {
    ASSERT_THROW(AssetExchange_from_str("invalid_exchange"), std::invalid_argument);
}

TEST(AssetExchangeTest, IsAssetExchange) {
    ASSERT_TRUE(is_AssetExchange("AMEX"));
    ASSERT_TRUE(is_AssetExchange("ARCA"));
    ASSERT_TRUE(is_AssetExchange("BATS"));
    ASSERT_TRUE(is_AssetExchange("NYSE"));
    ASSERT_TRUE(is_AssetExchange("NASDAQ"));
    ASSERT_TRUE(is_AssetExchange("NYSEARCA"));
    ASSERT_TRUE(is_AssetExchange("FTXU"));
    ASSERT_TRUE(is_AssetExchange("CBSE"));
    ASSERT_TRUE(is_AssetExchange("GNSS"));
    ASSERT_TRUE(is_AssetExchange("ERSX"));
    ASSERT_TRUE(is_AssetExchange("OTC"));
    ASSERT_TRUE(is_AssetExchange("CRYPTO"));
    ASSERT_TRUE(is_AssetExchange("EMPTY"));
    ASSERT_FALSE(is_AssetExchange("invalid_exchange"));
}
