#pragma once
#include <string>
#include <optional>
#include "vp/QueryBuilder.h"

namespace vp {

/**
 * @brief Request parameters for getting portfolio history
 */
struct GetPortfolioHistoryRequest
{
  std::optional<std::string> period;
  std::optional<std::string> timeframe;
  std::optional<std::string> intraday_reporting;
  std::optional<std::string> start;
  std::optional<std::string> end;
  std::optional<std::string> date_end;
  std::optional<bool> extended_hours;
  std::optional<std::string> pnl_reset;
  std::optional<std::string> cashflow_types;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    qb.add("period", period);
    qb.add("timeframe", timeframe);
    qb.add("intraday_reporting", intraday_reporting);
    qb.add("start", start);
    qb.add("end", end);
    qb.add("date_end", date_end);
    qb.add("extended_hours", extended_hours);
    qb.add("pnl_reset", pnl_reset);
    qb.add("cashflow_types", cashflow_types);
    return qb.build();
  }
};

} // namespace vp
