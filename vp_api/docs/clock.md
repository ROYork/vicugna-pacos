# Get Market Clock Info
This document describes the "Get Market Clock info" API endpoint.

## API Purpose
Provides details about the market clock, including its current status (open or closed) and upcoming open/close times.

`get https://paper-api.alpaca.markets/v2/clock`

## Base URL
https://paper-api.alpaca.markets/v2/clock

## GET Example using CURL
```bash
curl --request GET \
     --url https://paper-api.alpaca.markets/v2/clock \
     --header 'APCA-API-KEY-ID: HIDDENPRIVATEKEYVAL0' \
     --header 'APCA-API-SECRET-KEY: HiddenPrivateObfusfatedSecretApacaKey4pt' \               
     --header 'accept: application/json'
```
## Response Body Description 

The response body includes the following fields:

*   `timestamp`: Current timestamp (date-time).
*   `is_open`: Indicates whether the market is open (boolean).
*   `next_open`: Timestamp for the next market open (date-time).
*   `next_close`: Timestamp for the next market close (date-time).

## Response Body JSON Example 
```json
{
  "is_open": false,
  "next_close": "2025-08-11T16:00:00-04:00",
  "next_open": "2025-08-11T09:30:00-04:00",
  "timestamp": "2025-08-10T17:00:21.687289353-04:00"
}
``` 


## Source
Information extracted from: https://docs.alpaca.markets/reference/getclock-1
