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
#include "vp/AccountConfiguration.h"
#include "vp/Order.h"
#include "vp/Position.h"
#include "vp/Asset.h"
#include "vp/Calendar.h"
#include "vp/Watchlist.h"
#include "vp/PortfolioHistory.h"
#include "vp/OptionContract.h"
#include "vp/CancelOrderResponse.h"
#include "vp/ClosePositionResponse.h"
#include "vp/TradeUpdate.h"
#include "vp/GetOrdersRequest.h"
#include "vp/GetOrderByIdRequest.h"
#include "vp/ReplaceOrderRequest.h"
#include "vp/OrderRequest.h"
#include "vp/ClosePositionRequest.h"
#include "vp/GetCalendarRequest.h"
#include "vp/GetAssetsRequest.h"
#include "vp/GetPortfolioHistoryRequest.h"
#include "vp/CreateWatchlistRequest.h"
#include "vp/UpdateWatchlistRequest.h"
#include "vp/GetOptionContractsRequest.h"

namespace vp {


class TradingClient
{
public:

  TradingClient(const std::string& api_key,
                const std::string& api_secret,
                bool paper = true,
                const std::string& url_override = "");

  // ===== REST API Methods =====

  /// Get current market clock information
  vp::Clock get_clock();

  /// Get account information
  vp::Account get_account();

  // ===== Positions =====

  /// Get all open positions
  std::vector<vp::Position> get_positions();

  /// Get a specific position by symbol
  std::optional<vp::Position> get_position(
    const std::string& symbol);

  /// Close all positions
  std::vector<vp::ClosePositionResponse> close_all_positions(
    std::optional<bool> cancel_orders = std::nullopt);

  /// Close a specific position
  vp::Order close_position(
    const std::string& symbol_or_asset_id,
    const ClosePositionRequest& close_options = {});

  /// Exercise an options position
  void exercise_options_position(
    const std::string& symbol_or_contract_id);

  // ===== Orders =====

  /// Get all orders with filter
  std::vector<vp::Order> get_orders(
    const GetOrdersRequest& filter);

  /// Get a specific order by ID
  std::optional<vp::Order> get_order_by_id(
    const std::string& order_id,
    const GetOrderByIdRequest& filter = {});

  /// Get a specific order by client order ID
  std::optional<vp::Order> get_order_by_client_id(
    const std::string& client_id);

  /// Submit a new order using OrderRequest
  vp::Order submit_order(const OrderRequest& order_data);

  /// Replace an existing order
  vp::Order replace_order_by_id(
    const std::string& order_id,
    const ReplaceOrderRequest& order_data);

  /// Cancel an order by ID
  void cancel_order(const std::string& order_id);

  /// Cancel all open orders
  std::vector<vp::CancelOrderResponse> cancel_all_orders();

  // ===== Calendar + Assets =====

  /// Get market calendar
  std::vector<vp::Calendar> get_calendar(
    const GetCalendarRequest& filters = {});

  /// Get all assets
  std::vector<vp::Asset> get_all_assets(
    const GetAssetsRequest& filter = {});

  /// Get a specific asset
  std::optional<vp::Asset> get_asset(
    const std::string& symbol_or_asset_id);

  // ===== Account Configuration =====

  /// Get account configurations
  vp::AccountConfiguration get_account_configurations();

  /// Set account configurations
  vp::AccountConfiguration set_account_configurations(
    const vp::AccountConfiguration& config);

  // ===== Portfolio History =====

  /// Get portfolio history
  vp::PortfolioHistory get_portfolio_history(
    const GetPortfolioHistoryRequest& filter = {});

  // ===== Watchlists =====

  /// Get all watchlists
  std::vector<vp::Watchlist> get_watchlists();

  /// Get a specific watchlist
  std::optional<vp::Watchlist> get_watchlist_by_id(
    const std::string& watchlist_id);

  /// Create a watchlist
  vp::Watchlist create_watchlist(
    const CreateWatchlistRequest& data);

  /// Update a watchlist
  vp::Watchlist update_watchlist_by_id(
    const std::string& id,
    const UpdateWatchlistRequest& data);

  /// Add an asset to a watchlist
  vp::Watchlist add_asset_to_watchlist_by_id(
    const std::string& id,
    const std::string& symbol);

  /// Delete a watchlist
  void delete_watchlist_by_id(const std::string& watchlist_id);

  /// Remove an asset from a watchlist
  vp::Watchlist remove_asset_from_watchlist_by_id(
    const std::string& id,
    const std::string& symbol);

  // ===== Options Contracts =====

  /// Get option contracts
  vp::OptionContractsResponse get_option_contracts(
    const GetOptionContractsRequest& request);

  /// Get a specific option contract
  std::optional<vp::OptionContract> get_option_contract(
    const std::string& symbol_or_id);

  // ===== WebSocket Streaming =====

  /// Start WebSocket streaming for trade updates (raw)
  void start_trade_stream(
    std::function<void(const std::string&)> on_trade_update,
    std::function<void(const std::string&)> on_error = nullptr);

  /// Start WebSocket streaming for trade updates (typed)
  void start_trade_stream(
    std::function<void(const vp::TradeUpdate&)> on_trade_update,
    std::function<void(const std::string&)> on_error = nullptr);

  /// Stop WebSocket streaming
  void stop_trade_stream();

  // ===== Deprecated Methods =====

  /// @deprecated Use get_orders(GetOrdersRequest) instead
  [[deprecated("Use get_orders(GetOrdersRequest) instead")]]
  std::vector<vp::Order> get_orders(
    const std::string& status = "", int limit = 50);

  /// @deprecated Use get_order_by_id() instead
  [[deprecated("Use get_order_by_id() instead")]]
  std::optional<vp::Order> get_order(
    const std::string& order_id);

  /// @deprecated Use submit_order(OrderRequest) instead
  [[deprecated("Use submit_order(OrderRequest) instead")]]
  vp::Order submit_order(const std::string& symbol,
                         const std::string& qty,
                         OrderSide side,
                         OrderType type,
                         TimeInForce time_in_force,
                         std::optional<double> limit_price = std::nullopt,
                         std::optional<double> stop_price  = std::nullopt,
                         bool extended_hours               = false);

private:

  std::string m_api_key;
  std::string m_api_secret;
  std::string m_base_url;
  std::string m_stream_url;
  ix::WebSocketHttpHeaders m_headers;

  // WebSocket for streaming
  std::unique_ptr<ix::WebSocket> m_websocket;

  // Helper method for making HTTP requests
  ix::HttpResponsePtr make_request(const std::string& method,
                                   const std::string& endpoint,
                                   const std::string& body = "");
};

} // namespace vp
