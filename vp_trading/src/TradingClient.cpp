#include "vp/TradingClient.h"
#include "vp/alpaca_constants.h"
#include <stdexcept>
#include <glaze/glaze.hpp>
#include <sstream>

namespace vp {


TradingClient::TradingClient(const std::string& api_key,
                                       const std::string& api_secret,
                                       bool paper):
  m_api_key(api_key),
  m_api_secret(api_secret),
  m_base_url(paper ? BaseURL::TRADING_PAPER : BaseURL::TRADING_LIVE),
  m_stream_url(paper ? "wss://paper-api.alpaca.markets/stream" : "wss://api.alpaca.markets/stream")
{
  if (api_key.empty() || api_secret.empty())
  {
    throw std::invalid_argument("API key and secret cannot be empty");
  }
  m_headers = {
    {"APCA-API-KEY-ID", m_api_key},
    {"APCA-API-SECRET-KEY", m_api_secret},
    {"Content-Type", "application/json"}
  };
}

// ===== Helper Method =====

ix::HttpResponsePtr TradingClient::make_request(
  const std::string& method,
  const std::string& endpoint,
  const std::string& body)
{
  ix::HttpClient httpClient;
  ix::HttpRequestArgsPtr args = httpClient.createRequest();
  args->extraHeaders = m_headers;

  std::string url = m_base_url + endpoint;

  if (method == "GET")
  {
    return httpClient.get(url, args);
  }
  else if (method == "POST")
  {
    return httpClient.post(url, body, args);
  }
  else if (method == "DELETE")
  {
    return httpClient.Delete(url, args);
  }
  else
  {
    throw std::invalid_argument("Unsupported HTTP method: " + method);
  }
}

// ===== REST API Methods =====

vp::Clock TradingClient::get_clock()
{
  vp::Clock clock;
  auto response = make_request("GET", "/v2/clock");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(clock, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse clock response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error("Failed to get clock: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
  return clock;
}

vp::Account TradingClient::get_account()
{
  vp::Account account;
  auto response = make_request("GET", "/v2/account");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(account, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse account response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error("Failed to get account: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
  return account;
}

std::vector<vp::Position> TradingClient::get_positions()
{
  std::vector<vp::Position> positions;
  auto response = make_request("GET", "/v2/positions");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(positions, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse positions response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error("Failed to get positions: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
  return positions;
}

std::optional<vp::Position> TradingClient::get_position(const std::string& symbol)
{
  auto response = make_request("GET", "/v2/positions/" + symbol);

  if (response->statusCode == 200)
  {
    vp::Position position;
    auto error = glz::read_json(position, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse position response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
    return position;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;  // No position found
  }
  else
  {
    throw std::runtime_error("Failed to get position: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
}

std::vector<vp::Order> TradingClient::get_orders(const std::string& status, int limit)
{
  std::ostringstream endpoint;
  endpoint << "/v2/orders?limit=" << limit;
  if (!status.empty())
  {
    endpoint << "&status=" << status;
  }

  std::vector<vp::Order> orders;
  auto response = make_request("GET", endpoint.str());

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(orders, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse orders response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error("Failed to get orders: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
  return orders;
}

std::optional<vp::Order> TradingClient::get_order(const std::string& order_id)
{
  auto response = make_request("GET", "/v2/orders/" + order_id);

  if (response->statusCode == 200)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse order response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;  // No order found
  }
  else
  {
    throw std::runtime_error("Failed to get order: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
}

vp::Order TradingClient::submit_order(
  const std::string& symbol,
  const std::string& qty,
  OrderSide side,
  OrderType type,
  TimeInForce time_in_force,
  std::optional<double> limit_price,
  std::optional<double> stop_price,
  bool extended_hours)
{
  // Build JSON request body
  std::ostringstream json_body;
  json_body << "{";
  json_body << "\"symbol\":\"" << symbol << "\",";
  json_body << "\"qty\":\"" << qty << "\",";
  json_body << "\"side\":" << to_json(side) << ",";
  json_body << "\"type\":" << to_json(type) << ",";
  json_body << "\"time_in_force\":" << to_json(time_in_force);

  if (limit_price.has_value())
  {
    json_body << ",\"limit_price\":" << limit_price.value();
  }

  if (stop_price.has_value())
  {
    json_body << ",\"stop_price\":" << stop_price.value();
  }

  if (extended_hours)
  {
    json_body << ",\"extended_hours\":true";
  }

  json_body << "}";

  auto response = make_request("POST", "/v2/orders", json_body.str());

  if (response->statusCode == 200 || response->statusCode == 201)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse order response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else
  {
    throw std::runtime_error("Failed to submit order: " + std::to_string(response->statusCode) + " - " + response->body);
  }
}

void TradingClient::cancel_order(const std::string& order_id)
{
  auto response = make_request("DELETE", "/v2/orders/" + order_id);

  if (response->statusCode != 200 && response->statusCode != 204)
  {
    throw std::runtime_error("Failed to cancel order: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
}

std::vector<vp::Order> TradingClient::cancel_all_orders()
{
  std::vector<vp::Order> canceled_orders;
  auto response = make_request("DELETE", "/v2/orders");

  if (response->statusCode == 200 || response->statusCode == 207)
  {
    auto error = glz::read_json(canceled_orders, response->body);
    if (error)
    {
      throw std::runtime_error("Failed to parse cancel all orders response: " +
                               std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error("Failed to cancel all orders: " + std::to_string(response->statusCode) + " - " + response->errorMsg);
  }
  return canceled_orders;
}

// ===== WebSocket Streaming =====

void TradingClient::start_trade_stream(
  std::function<void(const std::string&)> on_trade_update,
  std::function<void(const std::string&)> on_error)
{
  m_websocket = std::make_unique<ix::WebSocket>();
  m_websocket->setUrl(m_stream_url);

  m_websocket->setOnMessageCallback([this, on_trade_update, on_error](const ix::WebSocketMessagePtr& msg)
  {
    if (msg->type == ix::WebSocketMessageType::Open)
    {
      // Authenticate
      std::ostringstream auth_msg;
      auth_msg << "{\"action\":\"authenticate\",\"data\":{";
      auth_msg << "\"key_id\":\"" << m_api_key << "\",";
      auth_msg << "\"secret_key\":\"" << m_api_secret << "\"";
      auth_msg << "}}";
      m_websocket->send(auth_msg.str());

      // Subscribe to trade updates
      std::string listen_msg = "{\"action\":\"listen\",\"data\":{\"streams\":[\"trade_updates\"]}}";
      m_websocket->send(listen_msg);
    }
    else if (msg->type == ix::WebSocketMessageType::Message)
    {
      if (on_trade_update)
      {
        on_trade_update(msg->str);
      }
    }
    else if (msg->type == ix::WebSocketMessageType::Error)
    {
      if (on_error)
      {
        on_error(msg->errorInfo.reason);
      }
    }
  });

  m_websocket->start();
}

void TradingClient::stop_trade_stream()
{
  if (m_websocket)
  {
    m_websocket->stop();
    m_websocket.reset();
  }
}


} // namespace vp
