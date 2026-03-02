#include "vp/TradingClient.h"
#include "vp/alpaca_constants.h"
#include <stdexcept>
#include <glaze/glaze.hpp>
#include <sstream>

namespace {

/// Alpaca WebSocket envelope: {"stream":"...","data":{...}}
struct TradeStreamEnvelope
{
  std::string stream;
  glz::raw_json data;
};

} // anonymous namespace

template <>
struct glz::meta<TradeStreamEnvelope>
{
  using T = TradeStreamEnvelope;
  static constexpr auto value = glz::object(
    "stream", &T::stream,
    "data", &T::data
  );
};

namespace vp {


TradingClient::TradingClient(const std::string& api_key,
                             const std::string& api_secret,
                             bool paper,
                             const std::string& url_override):
  m_api_key(api_key),
  m_api_secret(api_secret),
  m_base_url(url_override.empty()
    ? std::string(paper ? BaseURL::TRADING_PAPER : BaseURL::TRADING_LIVE)
    : url_override),
  m_stream_url(paper
    ? "wss://paper-api.alpaca.markets/stream"
    : "wss://api.alpaca.markets/stream")
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
  else if (method == "PUT")
  {
    return httpClient.put(url, body, args);
  }
  else if (method == "PATCH")
  {
    return httpClient.patch(url, body, args);
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
      throw std::runtime_error(
        "Failed to parse clock response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get clock: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return clock;
}

vp::Account TradingClient::get_account()
{
  auto response = make_request("GET", "/v2/account");

  if (response->statusCode == 200)
  {
    return vp::Account::from_json(response->body);
  }
  else
  {
    throw std::runtime_error(
      "Failed to get account: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

// ===== Positions =====

std::vector<vp::Position> TradingClient::get_positions()
{
  std::vector<vp::Position> positions;
  auto response = make_request("GET", "/v2/positions");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(positions, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse positions response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get positions: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return positions;
}

std::optional<vp::Position> TradingClient::get_position(
  const std::string& symbol)
{
  auto response = make_request("GET", "/v2/positions/" + symbol);

  if (response->statusCode == 200)
  {
    vp::Position position;
    auto error = glz::read_json(position, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse position response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return position;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get position: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

std::vector<vp::ClosePositionResponse> TradingClient::close_all_positions(
  std::optional<bool> cancel_orders)
{
  std::string endpoint = "/v2/positions";
  if (cancel_orders.has_value() && *cancel_orders)
  {
    endpoint += "?cancel_orders=true";
  }

  std::vector<vp::ClosePositionResponse> results;
  auto response = make_request("DELETE", endpoint);

  if (response->statusCode == 200 || response->statusCode == 207)
  {
    auto error = glz::read_json(results, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse close all positions response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to close all positions: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return results;
}

vp::Order TradingClient::close_position(
  const std::string& symbol_or_asset_id,
  const ClosePositionRequest& close_options)
{
  std::string endpoint =
    "/v2/positions/" + symbol_or_asset_id +
    close_options.to_query_string();

  auto response = make_request("DELETE", endpoint);

  if (response->statusCode == 200)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse close position response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else
  {
    throw std::runtime_error(
      "Failed to close position: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
}

void TradingClient::exercise_options_position(
  const std::string& symbol_or_contract_id)
{
  auto response = make_request(
    "POST",
    "/v2/positions/" + symbol_or_contract_id + "/exercise");

  if (response->statusCode != 200 && response->statusCode != 204)
  {
    throw std::runtime_error(
      "Failed to exercise options position: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
}

// ===== Orders =====

std::vector<vp::Order> TradingClient::get_orders(
  const GetOrdersRequest& filter)
{
  std::string endpoint = "/v2/orders" + filter.to_query_string();

  std::vector<vp::Order> orders;
  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(orders, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse orders response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get orders: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return orders;
}

std::optional<vp::Order> TradingClient::get_order_by_id(
  const std::string& order_id,
  const GetOrderByIdRequest& filter)
{
  std::string endpoint =
    "/v2/orders/" + order_id + filter.to_query_string();

  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse order response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get order: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

std::optional<vp::Order> TradingClient::get_order_by_client_id(
  const std::string& client_id)
{
  std::string endpoint =
    "/v2/orders:by_client_order_id?client_order_id=" + client_id;

  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse order response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get order by client ID: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

vp::Order TradingClient::submit_order(const OrderRequest& order_data)
{
  auto response = make_request("POST", "/v2/orders", order_data.to_json());

  if (response->statusCode == 200 || response->statusCode == 201)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse order response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else
  {
    throw std::runtime_error(
      "Failed to submit order: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
}

vp::Order TradingClient::replace_order_by_id(
  const std::string& order_id,
  const ReplaceOrderRequest& order_data)
{
  auto response = make_request(
    "PATCH", "/v2/orders/" + order_id, order_data.to_json());

  if (response->statusCode == 200)
  {
    vp::Order order;
    auto error = glz::read_json(order, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse replace order response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return order;
  }
  else
  {
    throw std::runtime_error(
      "Failed to replace order: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
}

void TradingClient::cancel_order(const std::string& order_id)
{
  auto response = make_request("DELETE", "/v2/orders/" + order_id);

  if (response->statusCode != 200 && response->statusCode != 204)
  {
    throw std::runtime_error(
      "Failed to cancel order: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

std::vector<vp::CancelOrderResponse> TradingClient::cancel_all_orders()
{
  std::vector<vp::CancelOrderResponse> canceled_orders;
  auto response = make_request("DELETE", "/v2/orders");

  if (response->statusCode == 200 || response->statusCode == 207)
  {
    auto error = glz::read_json(canceled_orders, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse cancel all orders response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to cancel all orders: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return canceled_orders;
}

// ===== Calendar + Assets =====

std::vector<vp::Calendar> TradingClient::get_calendar(
  const GetCalendarRequest& filters)
{
  std::string endpoint = "/v2/calendar" + filters.to_query_string();

  std::vector<vp::Calendar> calendar;
  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(calendar, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse calendar response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get calendar: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return calendar;
}

std::vector<vp::Asset> TradingClient::get_all_assets(
  const GetAssetsRequest& filter)
{
  std::string endpoint = "/v2/assets" + filter.to_query_string();

  std::vector<vp::Asset> assets;
  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(assets, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse assets response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get assets: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return assets;
}

std::optional<vp::Asset> TradingClient::get_asset(
  const std::string& symbol_or_asset_id)
{
  auto response = make_request(
    "GET", "/v2/assets/" + symbol_or_asset_id);

  if (response->statusCode == 200)
  {
    vp::Asset asset;
    auto error = glz::read_json(asset, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse asset response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return asset;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get asset: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

// ===== Account Configuration =====

vp::AccountConfiguration TradingClient::get_account_configurations()
{
  vp::AccountConfiguration config;
  auto response = make_request("GET", "/v2/account/configurations");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(config, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse account config response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get account configurations: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return config;
}

vp::AccountConfiguration TradingClient::set_account_configurations(
  const vp::AccountConfiguration& config)
{
  vp::AccountConfiguration result;
  auto response = make_request(
    "PATCH", "/v2/account/configurations", config.to_json());

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(result, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse account config response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to set account configurations: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
  return result;
}

// ===== Portfolio History =====

vp::PortfolioHistory TradingClient::get_portfolio_history(
  const GetPortfolioHistoryRequest& filter)
{
  std::string endpoint =
    "/v2/account/portfolio/history" + filter.to_query_string();

  vp::PortfolioHistory history;
  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(history, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse portfolio history response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get portfolio history: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return history;
}

// ===== Watchlists =====

std::vector<vp::Watchlist> TradingClient::get_watchlists()
{
  std::vector<vp::Watchlist> watchlists;
  auto response = make_request("GET", "/v2/watchlists");

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(watchlists, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse watchlists response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get watchlists: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return watchlists;
}

std::optional<vp::Watchlist> TradingClient::get_watchlist_by_id(
  const std::string& watchlist_id)
{
  auto response = make_request(
    "GET", "/v2/watchlists/" + watchlist_id);

  if (response->statusCode == 200)
  {
    vp::Watchlist watchlist;
    auto error = glz::read_json(watchlist, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse watchlist response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return watchlist;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

vp::Watchlist TradingClient::create_watchlist(
  const CreateWatchlistRequest& data)
{
  vp::Watchlist watchlist;
  auto response = make_request("POST", "/v2/watchlists", data.to_json());

  if (response->statusCode == 200 || response->statusCode == 201)
  {
    auto error = glz::read_json(watchlist, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse create watchlist response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to create watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
  return watchlist;
}

vp::Watchlist TradingClient::update_watchlist_by_id(
  const std::string& id,
  const UpdateWatchlistRequest& data)
{
  vp::Watchlist watchlist;
  auto response = make_request(
    "PUT", "/v2/watchlists/" + id, data.to_json());

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(watchlist, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse update watchlist response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to update watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
  return watchlist;
}

vp::Watchlist TradingClient::add_asset_to_watchlist_by_id(
  const std::string& id,
  const std::string& symbol)
{
  std::string body = "{\"symbol\":\"" + symbol + "\"}";
  vp::Watchlist watchlist;
  auto response = make_request(
    "POST", "/v2/watchlists/" + id, body);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(watchlist, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse add asset watchlist response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to add asset to watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
  return watchlist;
}

void TradingClient::delete_watchlist_by_id(
  const std::string& watchlist_id)
{
  auto response = make_request(
    "DELETE", "/v2/watchlists/" + watchlist_id);

  if (response->statusCode != 200 && response->statusCode != 204)
  {
    throw std::runtime_error(
      "Failed to delete watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

vp::Watchlist TradingClient::remove_asset_from_watchlist_by_id(
  const std::string& id,
  const std::string& symbol)
{
  vp::Watchlist watchlist;
  auto response = make_request(
    "DELETE", "/v2/watchlists/" + id + "/" + symbol);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(watchlist, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse remove asset watchlist response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to remove asset from watchlist: " +
      std::to_string(response->statusCode) +
      " - " + response->body);
  }
  return watchlist;
}

// ===== Options Contracts =====

vp::OptionContractsResponse TradingClient::get_option_contracts(
  const GetOptionContractsRequest& request)
{
  std::string endpoint =
    "/v2/options/contracts" + request.to_query_string();

  vp::OptionContractsResponse result;
  auto response = make_request("GET", endpoint);

  if (response->statusCode == 200)
  {
    auto error = glz::read_json(result, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse option contracts response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
  }
  else
  {
    throw std::runtime_error(
      "Failed to get option contracts: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
  return result;
}

std::optional<vp::OptionContract> TradingClient::get_option_contract(
  const std::string& symbol_or_id)
{
  auto response = make_request(
    "GET", "/v2/options/contracts/" + symbol_or_id);

  if (response->statusCode == 200)
  {
    vp::OptionContract contract;
    auto error = glz::read_json(contract, response->body);
    if (error)
    {
      throw std::runtime_error(
        "Failed to parse option contract response: " +
        std::to_string(static_cast<int>(error.ec)));
    }
    return contract;
  }
  else if (response->statusCode == 404)
  {
    return std::nullopt;
  }
  else
  {
    throw std::runtime_error(
      "Failed to get option contract: " +
      std::to_string(response->statusCode) +
      " - " + response->errorMsg);
  }
}

// ===== WebSocket Streaming =====

void TradingClient::start_trade_stream(
  std::function<void(const std::string&)> on_trade_update,
  std::function<void(const std::string&)> on_error)
{
  m_websocket = std::make_unique<ix::WebSocket>();
  m_websocket->setUrl(m_stream_url);

  m_websocket->setOnMessageCallback(
    [this, on_trade_update, on_error](
      const ix::WebSocketMessagePtr& msg)
    {
      if (msg->type == ix::WebSocketMessageType::Open)
      {
        std::ostringstream auth_msg;
        auth_msg << "{\"action\":\"authenticate\",\"data\":{";
        auth_msg << "\"key_id\":\"" << m_api_key << "\",";
        auth_msg << "\"secret_key\":\"" << m_api_secret << "\"";
        auth_msg << "}}";
        m_websocket->send(auth_msg.str());

        std::string listen_msg =
          "{\"action\":\"listen\",\"data\":"
          "{\"streams\":[\"trade_updates\"]}}";
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

void TradingClient::start_trade_stream(
  std::function<void(const vp::TradeUpdate&)> on_trade_update,
  std::function<void(const std::string&)> on_error)
{
  start_trade_stream(
    [on_trade_update, on_error](const std::string& raw_msg)
    {
      // Alpaca wraps trade updates in an envelope:
      // {"stream":"trade_updates","data":{...}}
      // Parse the envelope first to extract the data payload.
      TradeStreamEnvelope envelope;
      auto env_error = glz::read_json(envelope, raw_msg);
      if (env_error)
      {
        // Not an envelope format -- skip non-trade messages
        // (e.g., auth responses, listen confirmations)
        return;
      }

      if (envelope.stream != "trade_updates")
      {
        // Not a trade update message -- skip
        return;
      }

      vp::TradeUpdate update;
      auto error = glz::read_json(update, envelope.data.str);
      if (error)
      {
        if (on_error)
        {
          on_error("Failed to parse trade update: " + raw_msg);
        }
        return;
      }
      if (on_trade_update)
      {
        on_trade_update(update);
      }
    },
    on_error);
}

void TradingClient::stop_trade_stream()
{
  if (m_websocket)
  {
    m_websocket->stop();
    m_websocket.reset();
  }
}

// ===== Deprecated Methods =====

std::vector<vp::Order> TradingClient::get_orders(
  const std::string& status, int limit)
{
  GetOrdersRequest filter;
  if (!status.empty())
  {
    filter.status = QueryOrderStatus_from_str(status);
  }
  filter.limit = limit;
  return get_orders(filter);
}

std::optional<vp::Order> TradingClient::get_order(
  const std::string& order_id)
{
  return get_order_by_id(order_id);
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
  OrderRequest req;
  req.symbol = symbol;
  req.qty = qty;
  req.side = side;
  req.type = type;
  req.time_in_force = time_in_force;
  req.limit_price = limit_price;
  req.stop_price = stop_price;
  req.extended_hours = extended_hours;
  return submit_order(req);
}


} // namespace vp
