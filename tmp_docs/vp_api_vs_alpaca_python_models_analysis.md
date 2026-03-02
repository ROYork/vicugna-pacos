# vp_api vs Alpaca Python Trading Models: Deviation Report

## Scope
This report compares C++ structures and enums under `vp_api` against the Python reference models in:
- `build/_deps/alpaca_py-src/alpaca/trading/models.py`
- `build/_deps/alpaca_py-src/alpaca/trading/enums.py`

Primary C++ structure headers reviewed:
- `vp_api/include/vp/Account.h`
- `vp_api/include/vp/Order.h`
- `vp_api/include/vp/Position.h`
- `vp_api/include/vp/Clock.h`
- `vp_api/include/vp/Calendar.h`

## Executive Summary
The C++ `vp_api` currently mirrors only a subset of Alpaca Python trading models and has several notable schema drifts:
- `Order`, `Position`, and `Account` are missing multiple fields present in Python.
- C++ uses stronger/defaulted primitives where Python intentionally uses many `Optional[...]` values, changing semantics for missing/null fields.
- Enum drift exists in `AssetClass`, `AssetExchange`, and especially `TradeEvent`.
- `Calendar` semantics differ due to timezone handling (`Z`/UTC construction in C++ helper methods).

## Model Coverage
Python trading models found: 20 classes in `models.py`.

C++ structs in `vp_api/include/vp` relevant to trading models:
- `Account`
- `Order`
- `Position`
- `Clock`
- `Calendar`

Also present but outside trading `models.py` scope:
- `bar_t`, `BarSet`, `BarResp` in `vp_api/include/vp/alpaca_bars.h`

### Missing C++ Struct Equivalents (present in Python)
No direct C++ struct equivalent found for:
- `Asset`
- `USDPositionValues`
- `AllAccountsPositions`
- `FailedClosePositionDetails`
- `ClosePositionResponse`
- `PortfolioHistory`
- `Watchlist`
- `BaseActivity`
- `NonTradeActivity`
- `TradeActivity`
- `AccountConfiguration`
- `CorporateActionAnnouncement`
- `TradeUpdate`
- `OptionContract`
- `OptionContractsResponse`

## Detailed Structure Deviations

## 1) `Order`
C++: `vp_api/include/vp/Order.h`  
Python: `build/_deps/alpaca_py-src/alpaca/trading/models.py` (`class Order`)

### Missing fields in C++
Python fields missing in C++:
- `expires_at`
- `type`
- `legs`
- `trail_percent`
- `trail_price`
- `hwm`
- `position_intent`
- `ratio_qty`

### Nullability/type behavior deviations
- Python marks many order fields optional to represent API omissions/nulls (notably mleg behavior):
  - `asset_id`, `symbol`, `asset_class`, `side`, `type`, `order_type`, etc.
- C++ uses defaults/non-optional for several of these (e.g., `asset_id` as empty string, `asset_class` default `us_equity`, `side` default `buy`, `order_type` default `market`).

Impact:
- Missing vs intentionally omitted data can be conflated with defaults.
- Multi-leg options (`mleg`) response semantics can be distorted.

## 2) `Position`
C++: `vp_api/include/vp/Position.h`  
Python: `build/_deps/alpaca_py-src/alpaca/trading/models.py` (`class Position`)

### Missing fields in C++
Python fields missing in C++:
- `asset_marginable`
- `swap_rate`
- `avg_entry_swap_rate`
- `usd` (`USDPositionValues` nested model)

### Nullability/type behavior deviations
- Python uses string/optional-string for many numeric values (`avg_entry_price`, `market_value`, `cost_basis`, etc.) to preserve raw API precision/representation.
- C++ uses non-optional `double` for most of these.

Impact:
- Precision and representation differences.
- Null/absent values become indistinguishable from numeric defaults.

## 3) `Account` (mapped to Python `TradeAccount`)
C++: `vp_api/include/vp/Account.h`  
Python: `build/_deps/alpaca_py-src/alpaca/trading/models.py` (`class TradeAccount`)

### Missing fields in C++
Python fields missing in C++:
- `crypto_status`
- `pending_transfer_out`
- `pending_transfer_in`
- `options_buying_power`
- `options_approved_level`
- `options_trading_level`

### Nullability/type behavior deviations
- Python uses many `Optional[str]` values for account numeric quantities.
- C++ uses non-optional numeric primitives (`double`, `int`) for many of these fields.

Impact:
- Nullability/state loss and inability to represent omitted server values distinctly.

## 4) `Calendar`
C++: `vp_api/include/vp/Calendar.h`  
Python: `build/_deps/alpaca_py-src/alpaca/trading/models.py` (`class Calendar`)

### Field mismatch
- C++ includes extra field `settlement_date` not present in Python trading model.

### Semantic/timezone deviation
- Python converts `open`/`close` to datetimes by combining `date + HH:MM` without timezone attachment in model init.
- C++ helper methods `opens()`/`closes()` construct strings with `Z` (UTC) via `std::format("{}T{}:00.000000000Z", ...)`.

Impact:
- Potential timezone interpretation mismatch for market-session calculations.

## 5) `Clock`
C++: `vp_api/include/vp/Clock.h`  
Python: `build/_deps/alpaca_py-src/alpaca/trading/models.py` (`class Clock`)

Field set is aligned (`timestamp`, `is_open`, `next_open`, `next_close`).

Notable implementation difference:
- C++ stores timestamps as `std::string` and provides parser helpers.
- Python stores typed `datetime` values.

## Enum Deviations
Compared common enum names across `enums.py` and `vp_api/include/vp/*.h`.

### 1) `AssetClass`
- Python includes: `crypto_perp`
- C++ missing: `crypto_perp`

### 2) `AssetExchange`
- Python includes: `ASCX`
- C++ missing: `ASCX`

### 3) `TradeEvent`
Python has 12 values; C++ has 5.
Missing in C++:
- `accepted`
- `expired`
- `pending_cancel`
- `pending_replace`
- `rejected`
- `replaced`
- `restated`

Impact:
- Event stream/order-update handling can fail or reject valid values from Alpaca.

## Test Coverage Notes
From `vp_api/ut/CMakeLists.txt`:
- Present: `ut_Account.cpp`, `ut_Clock.cpp`, and many enum tests.
- Not present as dedicated tests: `Order`, `Position`, `Calendar` struct serialization/compatibility tests.

Impact:
- Core model parity issues for `Order`/`Position`/`Calendar` are less likely to be caught automatically.

## Notable Risks
- Serialization drift against upstream Alpaca API responses.
- Loss of nullability semantics due to defaulted non-optional C++ fields.
- Enum parse failures when Alpaca returns newer or currently-missing values.
- Timezone interpretation discrepancies in calendar operations.

## Suggested Remediation Priorities
1. Align `TradeEvent`, `AssetClass`, `AssetExchange` enum values.
2. Expand `Order` to include all missing fields and optional semantics for mleg-compatible fields.
3. Expand `Position` with missing swap/usd-related fields and reconsider numeric string handling.
4. Expand `Account` with missing options/transfer/crypto fields.
5. Add parity unit tests for `Order`, `Position`, and `Calendar` against real/reference JSON fixtures.

## File References
- `vp_api/include/vp/Account.h`
- `vp_api/include/vp/Order.h`
- `vp_api/include/vp/Position.h`
- `vp_api/include/vp/Clock.h`
- `vp_api/include/vp/Calendar.h`
- `vp_api/include/vp/AssetClass.h`
- `vp_api/include/vp/AssetExchange.h`
- `vp_api/include/vp/TradeEvent.h`
- `vp_api/include/vp/alpaca_bars.h`
- `vp_api/ut/CMakeLists.txt`
- `build/_deps/alpaca_py-src/alpaca/trading/models.py`
- `build/_deps/alpaca_py-src/alpaca/trading/enums.py`
