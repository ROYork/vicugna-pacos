#include <iostream>

//UUID Defs
#include <array>
#include <cstdint>
#include <string>
#include <stdexcept>
#include <charconv>
#include <cctype>
#include <cstring>

#include "vp/alpaca_common_enums.h"

#include "vp/TradingClient.h"
#include "vp/TradeActivityType.h"
#include "vp/Exchange.h"

const std::string DEFAULT_APCA_API_KEY  = "PK4ZXSGC70J64TFUCMD0";
const std::string DEFAULT_APCA_API_SECRET_KEY = "WeYDs37M8gTt9rsIcdfzh3g7peQGCK925iDgekpt";


int main()
{

  vp::TradingClient client(DEFAULT_APCA_API_KEY,
                               DEFAULT_APCA_API_SECRET_KEY);


  auto clk = client.get_clock();
  std::cout << clk.to_json() << std::endl;

  auto account = client.get_account();
  //std::cout <<
  // vp::TradeActivityType tradeAct = vp::TradeActivityType::partial_fill;
  // std::string jsonTradeType  = to_json(tradeAct);

  // std::cout << "TradeActivityType:" << jsonTradeType << std::endl;
  // std::cout << "TradeActivityType:" << to_str(tradeAct) << std::endl;

  // vp::Exchange exchange = vp::Exchange::A;
  // std::cout << "Exchange Long String: " << to_str_long(exchange) << std::endl;
  return 0;
}
