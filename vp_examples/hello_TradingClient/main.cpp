#include <cstdlib>
#include <iostream>
#include <string>

#include "vp/TradingClient.h"


int main()
{
  const char* api_key = std::getenv("APCA_API_KEY_ID");
  const char* api_secret = std::getenv("APCA_API_SECRET_KEY");

  if (!api_key || !api_secret) {
    std::cerr << "Error: APCA_API_KEY_ID and APCA_API_SECRET_KEY "
                 "environment variables must be set." << std::endl;
    return 1;
  }

  vp::TradingClient client(api_key, api_secret);


  auto clk = client.get_clock();
  std::cout << clk.to_json() << std::endl;

  auto account = client.get_account();
  std::cout << account.to_json() << std::endl;

  //std::cout <<
  // vp::TradeActivityType tradeAct = vp::TradeActivityType::partial_fill;
  // std::string jsonTradeType  = to_json(tradeAct);

  // std::cout << "TradeActivityType:" << jsonTradeType << std::endl;
  // std::cout << "TradeActivityType:" << to_str(tradeAct) << std::endl;

  // vp::Exchange exchange = vp::Exchange::A;
  // std::cout << "Exchange Long String: " << to_str_long(exchange) << std::endl;
  return 0;
}
