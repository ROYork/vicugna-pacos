#pragma once
#include <string>
#include <optional>
#include <vector>
#include "vp/QueryBuilder.h"
#include "vp/QueryOrderStatus.h"
#include "vp/OrderSide.h"

namespace vp {

/**
 * @brief Request parameters for filtering orders
 */
struct GetOrdersRequest
{
  std::optional<QueryOrderStatus> status;
  std::optional<int> limit;
  std::optional<std::string> after;
  std::optional<std::string> until;
  std::optional<std::string> direction;
  std::optional<bool> nested;
  std::optional<OrderSide> side;
  std::optional<std::vector<std::string>> symbols;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    if (status.has_value())
    {
      qb.add("status", to_str(*status));
    }
    qb.add("limit", limit);
    qb.add("after", after);
    qb.add("until", until);
    qb.add("direction", direction);
    qb.add("nested", nested);
    if (side.has_value())
    {
      qb.add("side", to_str(*side));
    }
    qb.add("symbols", symbols);
    return qb.build();
  }
};

} // namespace vp
