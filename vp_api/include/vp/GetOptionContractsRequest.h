#pragma once
#include <string>
#include <optional>
#include <vector>
#include "vp/QueryBuilder.h"
#include "vp/AssetStatus.h"
#include "vp/ContractType.h"
#include "vp/ExerciseStyle.h"

namespace vp {

/**
 * @brief Request parameters for getting option contracts
 */
struct GetOptionContractsRequest
{
  std::optional<std::vector<std::string>> underlying_symbols;
  std::optional<AssetStatus> status;
  std::optional<std::string> expiration_date;
  std::optional<std::string> expiration_date_gte;
  std::optional<std::string> expiration_date_lte;
  std::optional<std::string> root_symbol;
  std::optional<ContractType> type;
  std::optional<ExerciseStyle> style;
  std::optional<double> strike_price_gte;
  std::optional<double> strike_price_lte;
  std::optional<int> limit;
  std::optional<std::string> page_token;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    qb.add("underlying_symbols", underlying_symbols);
    if (status.has_value())
    {
      qb.add("status", to_str(*status));
    }
    qb.add("expiration_date", expiration_date);
    qb.add("expiration_date_gte", expiration_date_gte);
    qb.add("expiration_date_lte", expiration_date_lte);
    qb.add("root_symbol", root_symbol);
    if (type.has_value())
    {
      qb.add("type", to_str(*type));
    }
    if (style.has_value())
    {
      qb.add("style", to_str(*style));
    }
    qb.add("strike_price_gte", strike_price_gte);
    qb.add("strike_price_lte", strike_price_lte);
    qb.add("limit", limit);
    qb.add("page_token", page_token);
    return qb.build();
  }
};

} // namespace vp
