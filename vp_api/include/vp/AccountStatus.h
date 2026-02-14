#pragma once
#include <glaze/glaze.hpp>


namespace vp {

/**
 * @brief The various statuses each brokerage account can take during its lifetime
 *
 * see https://alpaca.markets/docs/broker/api-references/accounts/accounts/#account-status
 */
enum class AccountStatus
{
  ACCOUNT_CLOSED,     ///< "ACCOUNT_CLOSED"
  ACCOUNT_UPDATED,    ///< "ACCOUNT_UPDATED"
  ACTION_REQUIRED,    ///< "ACTION_REQUIRED"
  ACTIVE,             ///< "ACTIVE"
  AML_REVIEW,         ///< "AML_REVIEW"
  APPROVAL_PENDING,   ///< "APPROVAL_PENDING"
  APPROVED,           ///< "APPROVED"
  DISABLED,           ///< "DISABLED"
  DISABLE_PENDING,    ///< "DISABLE_PENDING"
  EDITED,             ///< "EDITED"
  INACTIVE,           ///< "INACTIVE"
  KYC_SUBMITTED,      ///< "KYC_SUBMITTED"
  LIMITED,            ///< "LIMITED"
  ONBOARDING,         ///< "ONBOARDING"
  PAPER_ONLY,         ///< "PAPER_ONLY"
  REAPPROVAL_PENDING, ///< "REAPPROVAL_PENDING"
  REJECTED,           ///< "REJECTED"
  RESUBMITTED,        ///< "RESUBMITTED"
  SIGNED_UP,          ///< "SIGNED_UP"
  SUBMISSION_FAILED,  ///< "SUBMISSION_FAILED"
  SUBMITTED           ///< "SUBMITTED"
};

} // namespace vp


// *****************************************************************************
// Enum Function declarations - Outside the alpca namespace
// *****************************************************************************
std::string to_json(vp::AccountStatus obj);
std::string to_str(vp::AccountStatus obj);
vp::AccountStatus AccountStatus_from_str(std::string_view str);
vp::AccountStatus AccountStatus_from_json(std::string_view str);
bool is_AccountStatus(std::string_view str);



// *****************************************************************************
// glz::meta information - Outside the alpca namespace
// *****************************************************************************

/// glz::meta information for AccountStatus
template <>
struct glz::meta<vp::AccountStatus>
{
  using enum vp::AccountStatus;
  static constexpr auto value = glz::enumerate(
    ACCOUNT_CLOSED,
    ACCOUNT_UPDATED,
    ACTION_REQUIRED,
    ACTIVE,
    AML_REVIEW,
    APPROVAL_PENDING,
    APPROVED,
    DISABLED,
    DISABLE_PENDING,
    EDITED,
    INACTIVE,
    KYC_SUBMITTED,
    LIMITED,
    ONBOARDING,
    PAPER_ONLY,
    REAPPROVAL_PENDING,
    REJECTED,
    RESUBMITTED,
    SIGNED_UP,
    SUBMISSION_FAILED,
    SUBMITTED
    );
};


// *****************************************************************************
// Enum Utility Function Implementations - Outside the alpca namespace
// *****************************************************************************


/**
 * @brief Returns a json text representation of the enum value wrapped in " characters:
 *  returns "ACCOUNT_CLOSED" or "ACCOUNT_UPDATED" for this enum.
 *  @code
 *  std::cout << to_json(vp::AccountStatus::ACCOUNT_CLOSED);
 *  // "ACCOUNT_CLOSED"
 *  @endcode
 */
inline std::string to_json(vp::AccountStatus obj)
{
  return glz::write_json(obj).value_or("AccountStatus::to_json::error");
}

/**
 * @brief Returns the raw text representation of the enum:
 *  returns ACCOUNT_CLOSED or ACCOUNT_UPDATED for this enum.
 *  @code
 *  std::cout << to_json(vp::AccountStatus::ACCOUNT_CLOSED);
 *  // ACCOUNT_CLOSED
 *  @endcode
 */
inline std::string to_str(vp::AccountStatus obj)
{
  std::string out =to_json(obj);
  return out.substr(1, out.size() - 2);
}

/**
 * @brief Convert a string_view to a vp::AccountStatus object.
 */
inline vp::AccountStatus AccountStatus_from_str(std::string_view str)
{
  vp::AccountStatus s;
  const std::string json = "\"" + std::string(str) + "\"";
  auto error = glz::read_json(s, json);
  if (error)
  {
    // Check to see if the user passed a json type wrapped in quotes.
    auto error2 = glz::read_json(s, str);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid AccountStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Convert a string_view to a vp::AccountStatus object.
 */
inline vp::AccountStatus AccountStatus_from_json(std::string_view str)
{
  vp::AccountStatus s;
  auto error = glz::read_json(s, str);
  if (error)
  {
    const std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return s;
    }
    throw std::invalid_argument("Invalid AccountStatus string: " + std::string(str));
  }
  return s;
}

/**
 * @brief Returns true if the string_view is a valid 'AccountStatus'.
 */
inline bool is_AccountStatus(std::string_view str)
{
  vp::AccountStatus s;

  auto error = glz::read_json(s, str);
  if(!error)
  {
    return true;
  }
  else
  {
    std::string json = "\"" + std::string(str) + "\"";
    auto error2 = glz::read_json(s, json);
    if(!error2)
    {
      return true;
    }
  }
  return false;
}