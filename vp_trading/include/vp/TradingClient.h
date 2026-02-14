#pragma once


#include <ixwebsocket/IXHttpClient.h>
#include <ixwebsocket/IXWebSocket.h>
#include <string>
#include <vector>
#include <optional>
#include <map>
#include <functional>

#include "vp/Clock.h"
#include "vp/Account.h"
#include "vp/Order.h"
#include "vp/Position.h"

namespace vp {


class TradingClient
{
public:

  TradingClient(const std::string& api_key,
                const std::string& api_secret,
                bool paper = true);

  // ===== REST API Methods =====

  /// Get current market clock information
  vp::Clock get_clock();

  /// Get account information
  vp::Account get_account();

  /// Get all open positions
  std::vector<vp::Position> get_positions();

  /// Get a specific position by symbol
  std::optional<vp::Position> get_position(const std::string& symbol);

  /// Get all orders (optional: filter by status, limit, etc.)
  std::vector<vp::Order> get_orders(const std::string& status = "", int limit = 50);

  /// Get a specific order by ID
  std::optional<vp::Order> get_order(const std::string& order_id);

  /// Submit a new order
  vp::Order submit_order(const std::string & symbol,
                             const std::string & qty,
                             OrderSide side,
                             OrderType type,
                             TimeInForce time_in_force,
                             std::optional<double> limit_price = std::nullopt,
                             std::optional<double> stop_price  = std::nullopt,
                             bool extended_hours               = false);

  /// Cancel an order by ID
  void cancel_order(const std::string& order_id);

  /// Cancel all open orders
  std::vector<vp::Order> cancel_all_orders();

  // ===== WebSocket Streaming =====

  /// Start WebSocket streaming for trade updates
  void start_trade_stream(std::function<void(const std::string &)> on_trade_update,
                          std::function<void(const std::string &)> on_error = nullptr);

  /// Stop WebSocket streaming
  void stop_trade_stream();

private:

  std::string m_api_key;
  std::string m_api_secret;
  std::string m_base_url;
  std::string m_stream_url;
  ix::WebSocketHttpHeaders m_headers;

  // WebSocket for streaming
  std::unique_ptr<ix::WebSocket> m_websocket;

  // Helper method for making HTTP requests
  ix::HttpResponsePtr make_request(const std::string & method,
                                   const std::string & endpoint,
                                   const std::string & body = "");
};

} // namespace vp
