#pragma once
#include <string>
#include <optional>
#include "vp/QueryBuilder.h"

namespace vp {

/**
 * @brief Request parameters for closing a position
 */
struct ClosePositionRequest
{
  std::optional<std::string> qty;
  std::optional<std::string> percentage;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    qb.add("qty", qty);
    qb.add("percentage", percentage);
    return qb.build();
  }
};

} // namespace vp
