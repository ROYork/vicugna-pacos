#include "gtest/gtest.h"
#include "vp/alpaca_common_enums.h"
#include <glaze/glaze.hpp>
#include "vp/TradeActivityType.h"
#include "vp/SupportedCurrencies.h"


TEST(AlpacaCommonEnums, SupportedCurrencies)
{
  {
    vp::SupportedCurrencies currency = vp::SupportedCurrencies::USD;
    std::string strUSD = to_json(currency);
    EXPECT_STREQ(strUSD.c_str(),"\"USD\"");
  }

  {
    vp::SupportedCurrencies currency = vp::SupportedCurrencies::GBP;
    std::string strGBP = to_json(currency);
    EXPECT_STREQ(strGBP.c_str(),"\"GBP\"");
    vp::SupportedCurrencies converted_currency =  SupportedCurrencies_from_json(strGBP);
    EXPECT_EQ(converted_currency,vp::SupportedCurrencies::GBP);

    //Check the from string case
    vp::SupportedCurrencies converted_currency_from_str =  SupportedCurrencies_from_str(strGBP);
    EXPECT_EQ(converted_currency_from_str,vp::SupportedCurrencies::GBP);
  }

  {
    vp::SupportedCurrencies currency = vp::SupportedCurrencies::EUR;
    std::string strEUR = to_str(currency);
    EXPECT_STREQ(strEUR.c_str(),"EUR");
  }

  {
    vp::SupportedCurrencies currency = vp::SupportedCurrencies::CAD;
    std::string strCAD = to_str(currency);
    EXPECT_STREQ(strCAD.c_str(),"CAD");
    vp::SupportedCurrencies converted_currency =  SupportedCurrencies_from_str(strCAD);
    EXPECT_EQ(converted_currency,vp::SupportedCurrencies::CAD);
  }
}

TEST(AlpacaCommonEnums, SupportedCurrenciesFrom)
{
  EXPECT_EQ(vp::SupportedCurrencies::USD,SupportedCurrencies_from_json("\"USD\""));
  EXPECT_EQ(vp::SupportedCurrencies::USD,SupportedCurrencies_from_json("USD"));

  EXPECT_EQ(vp::SupportedCurrencies::GBP,SupportedCurrencies_from_json("\"GBP\""));
  EXPECT_EQ(vp::SupportedCurrencies::GBP,SupportedCurrencies_from_json("GBP"));

  EXPECT_THROW(SupportedCurrencies_from_json("invalid"), std::invalid_argument);
  EXPECT_THROW(SupportedCurrencies_from_json("usd"), std::invalid_argument);
}

TEST(AlpacaCommonEnums, SupportedCurrenciesIsType)
{
  EXPECT_TRUE(is_SupportedCurrencies("USD"));
  EXPECT_TRUE(is_SupportedCurrencies("GBP"));
  EXPECT_TRUE(is_SupportedCurrencies("CHF"));

  EXPECT_TRUE(is_SupportedCurrencies("\"USD\""));
  EXPECT_TRUE(is_SupportedCurrencies("\"GBP\""));
  EXPECT_TRUE(is_SupportedCurrencies("\"CHF\""));

  EXPECT_FALSE(is_SupportedCurrencies("invalid"));
  EXPECT_FALSE(is_SupportedCurrencies("usd"));
  EXPECT_FALSE(is_SupportedCurrencies("gbp"));
}


TEST(AlpacaCommonEnums, TradeActivityType)
{
  {
    vp::TradeActivityType part = vp::TradeActivityType::partial_fill;
    std::string strPF = to_json(part);
    EXPECT_STREQ(strPF.c_str(),"\"partial_fill\"");
  }

  {
    vp::TradeActivityType fill = vp::TradeActivityType::fill;
    std::string strFILL = to_json(fill);
    EXPECT_STREQ(strFILL.c_str(),"\"fill\"");
    vp::TradeActivityType trade_activity =  TradeActivityType_from_json(strFILL);
    EXPECT_EQ(trade_activity,vp::TradeActivityType::fill);

    //Check the from string case
    vp::TradeActivityType trade_activityFromStr =  TradeActivityType_from_str(strFILL);
    EXPECT_EQ(trade_activityFromStr,vp::TradeActivityType::fill);
  }

  {
    vp::TradeActivityType part = vp::TradeActivityType::partial_fill;
    std::string strPF = to_str(part);
    EXPECT_STREQ(strPF.c_str(),"partial_fill");
  }

  {
    vp::TradeActivityType fill = vp::TradeActivityType::fill;
    std::string strFILL = to_str(fill);
    EXPECT_STREQ(strFILL.c_str(),"fill");
    vp::TradeActivityType trade_activity =  TradeActivityType_from_str(strFILL);
    EXPECT_EQ(trade_activity,vp::TradeActivityType::fill);

    //vp::TradeActivityType trade_activityFromJson =  TradeActivityType_from_json(strFILL);
    //EXPECT_EQ(trade_activityFromJson,vp::TradeActivityType::fill);
  }

}
TEST(AlpacaCommonEnums, TradeActivityTypeFrom)
{
  EXPECT_EQ(vp::TradeActivityType::fill,TradeActivityType_from_json("\"fill\""));
  EXPECT_EQ(vp::TradeActivityType::fill,TradeActivityType_from_json("fill"));

  EXPECT_THROW(TradeActivityType_from_json("2022-01-12T25:18:44.100844Z"), std::invalid_argument);
  EXPECT_THROW(TradeActivityType_from_json("TradeActivityType"), std::invalid_argument);
  EXPECT_THROW(TradeActivityType_from_json("FILL"), std::invalid_argument);
}

TEST(AlpacaCommonEnums, TradeActivityIsType)
{
  EXPECT_TRUE(is_TradeActivityType("fill"));
  EXPECT_TRUE(is_TradeActivityType("partial_fill"));

  EXPECT_TRUE(is_TradeActivityType("\"fill\""));
  EXPECT_TRUE(is_TradeActivityType("\"partial_fill\""));

  EXPECT_FALSE(is_TradeActivityType("\"partial\""));
  EXPECT_FALSE(is_TradeActivityType("partial-fill"));
  EXPECT_FALSE(is_TradeActivityType("Partial_Fill"));
}



TEST(AlpacaCommonEnums, PaginationType)
{
  {
    vp::PaginationType none = vp::PaginationType::none;
    std::string strNone = to_json(none);
    EXPECT_STREQ(strNone.c_str(),"\"none\"");
  }

  {
    vp::PaginationType full = vp::PaginationType::full;
    std::string strFull = to_json(full);
    EXPECT_STREQ(strFull.c_str(),"\"full\"");
    vp::PaginationType pagination_type =  PaginationType_from_json(strFull);
    EXPECT_EQ(pagination_type,vp::PaginationType::full);

    //Check the from string case
    vp::PaginationType pagination_typeFromStr =  PaginationType_from_str(strFull);
    EXPECT_EQ(pagination_typeFromStr,vp::PaginationType::full);
  }

  {
    vp::PaginationType iterator = vp::PaginationType::iterator;
    std::string strIterator = to_json(iterator);
    EXPECT_STREQ(strIterator.c_str(),"\"iterator\"");
  }

  {
    vp::PaginationType none = vp::PaginationType::none;
    std::string strNone = to_str(none);
    EXPECT_STREQ(strNone.c_str(),"none");
  }

  {
    vp::PaginationType full = vp::PaginationType::full;
    std::string strFull = to_str(full);
    EXPECT_STREQ(strFull.c_str(),"full");
    vp::PaginationType pagination_type =  PaginationType_from_str(strFull);
    EXPECT_EQ(pagination_type,vp::PaginationType::full);
  }

  {
    vp::PaginationType iterator = vp::PaginationType::iterator;
    std::string strIterator = to_str(iterator);
    EXPECT_STREQ(strIterator.c_str(),"iterator");
  }
}

TEST(AlpacaCommonEnums, PaginationTypeFrom)
{
  EXPECT_EQ(vp::PaginationType::none,PaginationType_from_json("\"none\""));
  EXPECT_EQ(vp::PaginationType::none,PaginationType_from_json("none"));

  EXPECT_EQ(vp::PaginationType::full,PaginationType_from_json("\"full\""));
  EXPECT_EQ(vp::PaginationType::full,PaginationType_from_json("full"));

  EXPECT_EQ(vp::PaginationType::iterator,PaginationType_from_json("\"iterator\""));
  EXPECT_EQ(vp::PaginationType::iterator,PaginationType_from_json("iterator"));

  EXPECT_THROW(PaginationType_from_json("invalid"), std::invalid_argument);
  EXPECT_THROW(PaginationType_from_json("NONE"), std::invalid_argument);
}

TEST(AlpacaCommonEnums, PaginationIsType)
{
  EXPECT_TRUE(is_PaginationType("none"));
  EXPECT_TRUE(is_PaginationType("full"));
  EXPECT_TRUE(is_PaginationType("iterator"));

  EXPECT_TRUE(is_PaginationType("\"none\""));
  EXPECT_TRUE(is_PaginationType("\"full\""));
  EXPECT_TRUE(is_PaginationType("\"iterator\""));

  EXPECT_FALSE(is_PaginationType("invalid"));
  EXPECT_FALSE(is_PaginationType("None"));
  EXPECT_FALSE(is_PaginationType("FULL"));
}

TEST(AlpacaCommonEnums, SortType)
{
  {
    vp::Sort asc = vp::Sort::asc;
    std::string strAsc = to_json(asc);
    EXPECT_STREQ(strAsc.c_str(),"\"asc\"");
  }

  {
    vp::Sort desc = vp::Sort::desc;
    std::string strDesc = to_json(desc);
    EXPECT_STREQ(strDesc.c_str(),"\"desc\"");
    vp::Sort sort_type =  Sort_from_json(strDesc);
    EXPECT_EQ(sort_type,vp::Sort::desc);

    //Check the from string case
    vp::Sort sort_typeFromStr =  Sort_from_str(strDesc);
    EXPECT_EQ(sort_typeFromStr,vp::Sort::desc);
  }

  {
    vp::Sort asc = vp::Sort::asc;
    std::string strAsc = to_str(asc);
    EXPECT_STREQ(strAsc.c_str(),"asc");
  }

  {
    vp::Sort desc = vp::Sort::desc;
    std::string strDesc = to_str(desc);
    EXPECT_STREQ(strDesc.c_str(),"desc");
    vp::Sort sort_type =  Sort_from_str(strDesc);
    EXPECT_EQ(sort_type,vp::Sort::desc);
  }
}

TEST(AlpacaCommonEnums, SortTypeFrom)
{
  EXPECT_EQ(vp::Sort::asc,Sort_from_json("\"asc\""));
  EXPECT_EQ(vp::Sort::asc,Sort_from_json("asc"));

  EXPECT_EQ(vp::Sort::desc,Sort_from_json("\"desc\""));
  EXPECT_EQ(vp::Sort::desc,Sort_from_json("desc"));

  EXPECT_THROW(Sort_from_json("invalid"), std::invalid_argument);
  EXPECT_THROW(Sort_from_json("ASC"), std::invalid_argument);
}

TEST(AlpacaCommonEnums, SortIsType)
{
  EXPECT_TRUE(is_Sort("asc"));
  EXPECT_TRUE(is_Sort("desc"));

  EXPECT_TRUE(is_Sort("\"asc\""));
  EXPECT_TRUE(is_Sort("\"desc\""));

  EXPECT_FALSE(is_Sort("invalid"));
  EXPECT_FALSE(is_Sort("Asc"));
  EXPECT_FALSE(is_Sort("DESC"));
}
