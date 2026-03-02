#pragma once
#include <string>
#include <optional>
#include "vp/QueryBuilder.h"

namespace vp {

/**
 * @brief Request parameters for getting an order by ID
 */
struct GetOrderByIdRequest
{
  std::optional<bool> nested;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    qb.add("nested", nested);
    return qb.build();
  }
};

} // namespace vp
