#pragma once
#include <string>
#include <optional>
#include "vp/QueryBuilder.h"

namespace vp {

/**
 * @brief Request parameters for getting market calendar
 */
struct GetCalendarRequest
{
  std::optional<std::string> start;
  std::optional<std::string> end;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    qb.add("start", start);
    qb.add("end", end);
    return qb.build();
  }
};

} // namespace vp
