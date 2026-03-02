#include <cstdlib>
#include <iostream>
#include <string>

#include <curl/curl.h>

static size_t write_callback(void* contents, size_t size, size_t nmemb, void* userp)
{
  const size_t total_size = size * nmemb;
  auto* response = static_cast<std::string*>(userp);
  response->append(static_cast<char*>(contents), total_size);
  return total_size;
}

std::string get_assets(CURL *hnd,
                        const char* api_key,
                        const char* api_secret)
{
  if (!hnd) {
    return "Failed to initialize CURL handle.";
  }

  std::string response_body;
  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response_body);
  curl_easy_setopt(hnd, CURLOPT_URL, "https://paper-api.alpaca.markets/v2/assets");

  struct curl_slist *headers = NULL;
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

/**
 * @brief Get the asset model for a given symbol or asset_id. The symbol or asset_id should be passed in as a path parameter.
 *
 * Note: For crypto, the symbol has to follow old symbology, e.g. BTCUSD.
 * Note: For coin pairs, the symbol should be separated by spare symbol (/), e.g. BTC/USDT. Since spare is a special character in HTTP, use the URL encoded version instead, e.g. /v2/assets/BTC%2FUSDT
 *
 * Base URL : https://paper-api.alpaca.markets/v2/assets/{symbol_or_asset_id}
 * 
 * Example URL: https://docs.alpaca.markets/reference/get-v2-assets-symbol_or_asset_id
 */
std::string get_asset_by_id(CURL *hnd,
                            const char* api_key,
                            const char* api_secret,
                            const char* asset_id)
{
  if (!hnd) 
  {
    return "Failed to initialize CURL handle.";
  }
  
  std::string response_body;
  curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "GET");
  curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(hnd, CURLOPT_WRITEDATA, &response_body);
  curl_easy_setopt(hnd, CURLOPT_URL, "https://paper-api.alpaca.markets/v2/assets?status=active&attributes=");

  const std::string key_header = std::string("APCA-API-KEY-ID: ") + api_key;
  const std::string secret_header = std::string("APCA-API-SECRET-KEY: ") + api_secret;

  struct curl_slist *headers = NULL;
  headers = curl_slist_append(headers, "accept: application/json");
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
