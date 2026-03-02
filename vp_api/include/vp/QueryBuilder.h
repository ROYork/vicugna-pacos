#pragma once

#include <string>
#include <optional>
#include <sstream>
#include <vector>

namespace vp {

/**
 * @brief Builds URL query strings from optional fields
 *
 * Used by request structs to generate query parameters for
 * GET requests. Supports string, int, bool, double, and enum
 * types (via existing to_str() functions).
 */
class QueryBuilder
{
public:
  QueryBuilder& add(const std::string& key, const std::string& value)
  {
    if (!value.empty())
    {
      m_params.emplace_back(key, value);
    }
    return *this;
  }

  QueryBuilder& add(const std::string& key,
                     const std::optional<std::string>& value)
  {
    if (value.has_value() && !value->empty())
    {
      m_params.emplace_back(key, *value);
    }
    return *this;
  }

  QueryBuilder& add(const std::string& key,
                     const std::optional<int>& value)
  {
    if (value.has_value())
    {
      m_params.emplace_back(key, std::to_string(*value));
    }
    return *this;
  }

  QueryBuilder& add(const std::string& key,
                     const std::optional<double>& value)
  {
    if (value.has_value())
    {
      m_params.emplace_back(key, std::to_string(*value));
    }
    return *this;
  }

  QueryBuilder& add(const std::string& key,
                     const std::optional<bool>& value)
  {
    if (value.has_value())
    {
      m_params.emplace_back(key, *value ? "true" : "false");
    }
    return *this;
  }

  QueryBuilder& add_bool(const std::string& key, bool value)
  {
    m_params.emplace_back(key, value ? "true" : "false");
    return *this;
  }

  QueryBuilder& add_int(const std::string& key, int value)
  {
    m_params.emplace_back(key, std::to_string(value));
    return *this;
  }

  /// Add a vector of strings as comma-separated value
  QueryBuilder& add(const std::string& key,
                     const std::optional<std::vector<std::string>>& value)
  {
    if (value.has_value() && !value->empty())
    {
      std::ostringstream oss;
      for (size_t i = 0; i < value->size(); ++i)
      {
        if (i > 0)
        {
          oss << ",";
        }
        oss << (*value)[i];
      }
      m_params.emplace_back(key, oss.str());
    }
    return *this;
  }

  std::string build() const
  {
    if (m_params.empty())
    {
      return "";
    }

    std::ostringstream oss;
    oss << "?";
    for (size_t i = 0; i < m_params.size(); ++i)
    {
      if (i > 0)
      {
        oss << "&";
      }
      oss << m_params[i].first << "=" << m_params[i].second;
    }
    return oss.str();
  }

private:
  std::vector<std::pair<std::string, std::string>> m_params;
};

} // namespace vp
