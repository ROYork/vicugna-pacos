#include "gtest/gtest.h"
#include "vp/alpaca_bars.h"
#include <glaze/glaze.hpp>

TEST(AlpacaBarsTest, BarTMembers)
{
    vp::bar_t bar;
    bar.t = "2023-01-01T00:00:00Z";
    bar.o = 100.0;
    bar.h = 105.0;
    bar.l = 95.0;
    bar.c = 103.0;
    bar.v = 1000;
    bar.n = 100;
    bar.vw = 101.5;

    ASSERT_EQ(bar.t, "2023-01-01T00:00:00Z");
    ASSERT_EQ(bar.open(), 100.0);
    ASSERT_EQ(bar.high(), 105.0);
    ASSERT_EQ(bar.low(), 95.0);
    ASSERT_EQ(bar.close(), 103.0);
    ASSERT_EQ(bar.volume(), 1000);
    ASSERT_EQ(bar.trade_count(), 100);
    ASSERT_EQ(bar.vwap().value(), 101.5);

    // Test setters
    bar.open() = 101.0;
    ASSERT_EQ(bar.o, 101.0);
}

TEST(AlpacaBarsTest, BarTToJson)
{
  vp::bar_t bar;
  bar.t = "2023-01-01T00:00:00Z";
  bar.o = 100.0;
  bar.h = 105.0;
  bar.l = 95.123;
  bar.c = 103.0;
  bar.v = 1000;
  bar.n = 100;
  bar.vw = 101.5;

  std::string json_string = bar.to_json();
  ASSERT_FALSE(json_string.empty());

  // Verify some key elements in the JSON string
  ASSERT_NE(json_string.find("\"t\":\"2023-01-01T00:00:00Z\""), std::string::npos);
  ASSERT_NE(json_string.find("\"o\":100"), std::string::npos);
  ASSERT_NE(json_string.find("\"h\":105"), std::string::npos);
  ASSERT_NE(json_string.find("\"l\":95.123"), std::string::npos);
  ASSERT_NE(json_string.find("\"c\":103"), std::string::npos);
  ASSERT_NE(json_string.find("\"v\":1000"), std::string::npos);
  ASSERT_NE(json_string.find("\"n\":100"), std::string::npos);
  ASSERT_NE(json_string.find("\"vw\":101.5"), std::string::npos);

  vp::bar_t bar2 = vp::bar_t::from_json(bar.to_json());
  ASSERT_TRUE(bar==bar2);
  ASSERT_FALSE(bar!=bar2);
}


TEST(AlpacaBarsTest, BarT_Operators)
{
  vp::bar_t bar;
  bar.t = "2023-01-01T00:00:00Z";
  bar.o = 100.0;
  bar.h = 105.0;
  bar.l = 95.123;
  bar.c = 103.0;
  bar.v = 1000;
  bar.n = 100;
  bar.vw = 101.5;
  auto bar2=bar;
  ASSERT_TRUE(bar == bar2);
  ASSERT_FALSE(bar!= bar2);

  vp::bar_t defaultBar;
  ASSERT_TRUE(bar != defaultBar);

}
TEST(AlpacaBarsTest, BarT_Setters)
{
  vp::bar_t bar;
  bar.t = "2023-01-01T00:00:00Z";
  bar.o = 100.0;
  bar.h = 105.0;
  bar.l = 95.123;
  bar.c = 103.0;
  bar.v = 1000;
  bar.n = 100;
  bar.vw = 101.5;
  auto bar2=bar;
  ASSERT_TRUE(bar == bar2);
  ASSERT_FALSE(bar!= bar2);

  vp::bar_t defaultBar;
  ASSERT_TRUE(bar != defaultBar);

}

TEST(AlpacaBarsTest, BarRespAddAndFromJson)
{
    vp::BarResp bar_resp;
    vp::bar_t bar1;
    bar1.t = "2023-01-01T00:00:00Z";
    bar1.o = 100.0;

    vp::bar_t bar2;
    bar2.t = "2023-01-01T00:01:00Z";
    bar2.o = 101.0;

    bar_resp.add("AAPL", bar1);
    bar_resp.add("AAPL", bar2);
    bar_resp.add("GOOG", bar1);

    ASSERT_EQ(bar_resp.bars.size(), 2);
    ASSERT_EQ(bar_resp.bars["AAPL"].size(), 2);
    ASSERT_EQ(bar_resp.bars["GOOG"].size(), 1);
    ASSERT_EQ(bar_resp.bars["AAPL"][0].o, 100.0);
    ASSERT_EQ(bar_resp.bars["AAPL"][1].o, 101.0);
    ASSERT_EQ(bar_resp.bars["GOOG"][0].o, 100.0);

    std::string json_string = bar_resp.to_json();
    ASSERT_FALSE(json_string.empty());

    vp::BarResp new_bar_resp = vp::BarResp::from_json(json_string);
    ASSERT_EQ(new_bar_resp.bars.size(), 2);
    ASSERT_EQ(new_bar_resp.bars["AAPL"].size(), 2);
    ASSERT_EQ(new_bar_resp.bars["GOOG"].size(), 1);
    ASSERT_EQ(new_bar_resp.bars["AAPL"][0].o, 100.0);
    ASSERT_EQ(new_bar_resp.bars["AAPL"][1].o, 101.0);
    ASSERT_EQ(new_bar_resp.bars["GOOG"][0].o, 100.0);
}
