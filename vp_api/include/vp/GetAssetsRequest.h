#pragma once
#include <string>
#include <optional>
#include <vector>
#include "vp/QueryBuilder.h"
#include "vp/AssetStatus.h"
#include "vp/AssetClass.h"
#include "vp/AssetExchange.h"

namespace vp {

/**
 * @brief Request parameters for getting assets
 */
struct GetAssetsRequest
{
  std::optional<AssetStatus> status;
  std::optional<AssetClass> asset_class;
  std::optional<AssetExchange> exchange;
  std::optional<std::vector<std::string>> attributes;

  std::string to_query_string() const
  {
    QueryBuilder qb;
    if (status.has_value())
    {
      qb.add("status", to_str(*status));
    }
    if (asset_class.has_value())
    {
      qb.add("asset_class", to_str(*asset_class));
    }
    if (exchange.has_value())
    {
      qb.add("exchange", to_str(*exchange));
    }
    qb.add("attributes", attributes);
    return qb.build();
  }
};

} // namespace vp
