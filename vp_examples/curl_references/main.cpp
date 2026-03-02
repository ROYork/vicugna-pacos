#include <cstdlib>
#include <iostream>
#include <string>

#include <curl/curl.h>

#include "vp/TradingClient.h"

std::string get_account(CURL *hnd,
                        const char* api_key,
                        const char* api_secret);
std::string get_assets(CURL *hnd,
                       const char* api_key,
                       const char* api_secret);
std::string get_assets_active(CURL *hnd,
                              const char* api_key,
                              const char* api_secret);

std::string get_asset_by_id(CURL *hnd,
                            const char* api_key,
                            const char* api_secret,
                            const char* asset_id);
static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp);

static std::string perform_get(CURL* hnd,
                               const char* api_key,
                               const char* api_secret,
                               const char* url)
{
  if (!hnd)
  {
    return "Failed to initialize CURL handle.";
  }

  std::string response_body;
  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response_body);
  curl_easy_setopt(hnd, CURLOPT_URL, url);

  struct curl_slist* headers = nullptr;
  headers = curl_slist_append(headers, "accept: application/json");
  const std::string key_header = std::string("APCA-API-KEY-ID: ") + api_key;
  const std::string secret_header = std::string("APCA-API-SECRET-KEY: ") + api_secret;
  headers = curl_slist_append(headers, key_header.c_str());
  headers = curl_slist_append(headers, secret_header.c_str());
  curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);

  CURLcode ret = curl_easy_perform(hnd);
  long http_code = 0;
  curl_easy_getinfo(hnd, CURLINFO_RESPONSE_CODE, &http_code);
  curl_slist_free_all(headers);

  if (ret != CURLE_OK)
  {
    return "curl_easy_perform failed: " + std::string(curl_easy_strerror(ret));
  }
  if (http_code >= 200 && http_code < 300)
  {
    return response_body;
  }
  return "HTTP " + std::to_string(http_code) + ": " + response_body;
}

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
  const size_t total_size = size * nmemb;
  auto* response = static_cast<std::string*>(userp);
  response->append(static_cast<char*>(contents), total_size);
  return total_size;
}

int main()
{
  const char* api_key = std::getenv("APCA_API_KEY_ID");
  const char* api_secret = std::getenv("APCA_API_SECRET_KEY");

  if (!api_key || !api_secret) {
    std::cerr << "Error: APCA_API_KEY_ID and APCA_API_SECRET_KEY "
                 "environment variables must be set." << std::endl;
    return 1;
  }

  CURL *hnd = curl_easy_init();

  std::cout << "Get Account:" << std::endl;
  std::cout << get_account(hnd, api_key, api_secret) << std::endl;

  std::cout << "Get 'ALL' Assets:" << std::endl;
  std::cout << get_assets(hnd, api_key, api_secret) << std::endl;

  std::cout << "Get 'Active' Assets:" << std::endl;
  std::cout << get_assets_active(hnd, api_key, api_secret) << std::endl;

  curl_easy_cleanup(hnd);

  return 0;
}


/**
 * Fetches the account information from the Alpaca API using the provided CURL handle and API credentials.
 * Base URL: https://paper-api.alpaca.markets/v2/account
 */
std::string get_account(CURL *hnd,
                        const char* api_key,
                        const char* api_secret)
{
  return perform_get(
    hnd,
    api_key,
    api_secret,
    "https://paper-api.alpaca.markets/v2/account");
}

std::string get_assets_active(CURL *hnd,
                              const char* api_key,
                              const char* api_secret)
{
  return perform_get(
    hnd,
    api_key,
    api_secret,
    "https://paper-api.alpaca.markets/v2/assets?status=active");
}
