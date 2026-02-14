#include <gtest/gtest.h>
#include "vp/AccountStatus.h"

TEST(AccountStatusTest, ToString) {
    ASSERT_EQ("ACCOUNT_CLOSED", to_str(vp::AccountStatus::ACCOUNT_CLOSED));
    ASSERT_EQ("ACCOUNT_UPDATED", to_str(vp::AccountStatus::ACCOUNT_UPDATED));
    ASSERT_EQ("ACTION_REQUIRED", to_str(vp::AccountStatus::ACTION_REQUIRED));
    ASSERT_EQ("ACTIVE", to_str(vp::AccountStatus::ACTIVE));
    ASSERT_EQ("AML_REVIEW", to_str(vp::AccountStatus::AML_REVIEW));
    ASSERT_EQ("APPROVAL_PENDING", to_str(vp::AccountStatus::APPROVAL_PENDING));
    ASSERT_EQ("APPROVED", to_str(vp::AccountStatus::APPROVED));
    ASSERT_EQ("DISABLED", to_str(vp::AccountStatus::DISABLED));
    ASSERT_EQ("DISABLE_PENDING", to_str(vp::AccountStatus::DISABLE_PENDING));
    ASSERT_EQ("EDITED", to_str(vp::AccountStatus::EDITED));
    ASSERT_EQ("INACTIVE", to_str(vp::AccountStatus::INACTIVE));
    ASSERT_EQ("KYC_SUBMITTED", to_str(vp::AccountStatus::KYC_SUBMITTED));
    ASSERT_EQ("LIMITED", to_str(vp::AccountStatus::LIMITED));
    ASSERT_EQ("ONBOARDING", to_str(vp::AccountStatus::ONBOARDING));
    ASSERT_EQ("PAPER_ONLY", to_str(vp::AccountStatus::PAPER_ONLY));
    ASSERT_EQ("REAPPROVAL_PENDING", to_str(vp::AccountStatus::REAPPROVAL_PENDING));
    ASSERT_EQ("REJECTED", to_str(vp::AccountStatus::REJECTED));
    ASSERT_EQ("RESUBMITTED", to_str(vp::AccountStatus::RESUBMITTED));
    ASSERT_EQ("SIGNED_UP", to_str(vp::AccountStatus::SIGNED_UP));
    ASSERT_EQ("SUBMISSION_FAILED", to_str(vp::AccountStatus::SUBMISSION_FAILED));
    ASSERT_EQ("SUBMITTED", to_str(vp::AccountStatus::SUBMITTED));
}

TEST(AccountStatusTest, ToJsonString) {
  ASSERT_EQ("\"ACCOUNT_CLOSED\"", to_json(vp::AccountStatus::ACCOUNT_CLOSED));
  ASSERT_EQ("\"ACCOUNT_UPDATED\"", to_json(vp::AccountStatus::ACCOUNT_UPDATED));
  ASSERT_EQ("\"ACTION_REQUIRED\"", to_json(vp::AccountStatus::ACTION_REQUIRED));
  ASSERT_EQ("\"ACTIVE\"", to_json(vp::AccountStatus::ACTIVE));
  ASSERT_EQ("\"AML_REVIEW\"", to_json(vp::AccountStatus::AML_REVIEW));
  ASSERT_EQ("\"APPROVAL_PENDING\"", to_json(vp::AccountStatus::APPROVAL_PENDING));
  ASSERT_EQ("\"APPROVED\"", to_json(vp::AccountStatus::APPROVED));
  ASSERT_EQ("\"DISABLED\"", to_json(vp::AccountStatus::DISABLED));
  ASSERT_EQ("\"DISABLE_PENDING\"", to_json(vp::AccountStatus::DISABLE_PENDING));
  ASSERT_EQ("\"EDITED\"", to_json(vp::AccountStatus::EDITED));
  ASSERT_EQ("\"INACTIVE\"", to_json(vp::AccountStatus::INACTIVE));
  ASSERT_EQ("\"KYC_SUBMITTED\"", to_json(vp::AccountStatus::KYC_SUBMITTED));
  ASSERT_EQ("\"LIMITED\"", to_json(vp::AccountStatus::LIMITED));
  ASSERT_EQ("\"ONBOARDING\"", to_json(vp::AccountStatus::ONBOARDING));
  ASSERT_EQ("\"PAPER_ONLY\"", to_json(vp::AccountStatus::PAPER_ONLY));
  ASSERT_EQ("\"REAPPROVAL_PENDING\"", to_json(vp::AccountStatus::REAPPROVAL_PENDING));
  ASSERT_EQ("\"REJECTED\"", to_json(vp::AccountStatus::REJECTED));
  ASSERT_EQ("\"RESUBMITTED\"", to_json(vp::AccountStatus::RESUBMITTED));
  ASSERT_EQ("\"SIGNED_UP\"", to_json(vp::AccountStatus::SIGNED_UP));
  ASSERT_EQ("\"SUBMISSION_FAILED\"", to_json(vp::AccountStatus::SUBMISSION_FAILED));
  ASSERT_EQ("\"SUBMITTED\"", to_json(vp::AccountStatus::SUBMITTED));
}

TEST(AccountStatusTest, FromString) {
    ASSERT_EQ(vp::AccountStatus::ACCOUNT_CLOSED, AccountStatus_from_str("ACCOUNT_CLOSED"));
    ASSERT_EQ(vp::AccountStatus::ACCOUNT_UPDATED, AccountStatus_from_str("ACCOUNT_UPDATED"));
    ASSERT_EQ(vp::AccountStatus::ACTION_REQUIRED, AccountStatus_from_str("ACTION_REQUIRED"));
    ASSERT_EQ(vp::AccountStatus::ACTIVE, AccountStatus_from_str("ACTIVE"));
    ASSERT_EQ(vp::AccountStatus::AML_REVIEW, AccountStatus_from_str("AML_REVIEW"));
    ASSERT_EQ(vp::AccountStatus::APPROVAL_PENDING, AccountStatus_from_str("APPROVAL_PENDING"));
    ASSERT_EQ(vp::AccountStatus::APPROVED, AccountStatus_from_str("APPROVED"));
    ASSERT_EQ(vp::AccountStatus::DISABLED, AccountStatus_from_str("DISABLED"));
    ASSERT_EQ(vp::AccountStatus::DISABLE_PENDING, AccountStatus_from_str("DISABLE_PENDING"));
    ASSERT_EQ(vp::AccountStatus::EDITED, AccountStatus_from_str("EDITED"));
    ASSERT_EQ(vp::AccountStatus::INACTIVE, AccountStatus_from_str("INACTIVE"));
    ASSERT_EQ(vp::AccountStatus::KYC_SUBMITTED, AccountStatus_from_str("KYC_SUBMITTED"));
    ASSERT_EQ(vp::AccountStatus::LIMITED, AccountStatus_from_str("LIMITED"));
    ASSERT_EQ(vp::AccountStatus::ONBOARDING, AccountStatus_from_str("ONBOARDING"));
    ASSERT_EQ(vp::AccountStatus::PAPER_ONLY, AccountStatus_from_str("PAPER_ONLY"));
    ASSERT_EQ(vp::AccountStatus::REAPPROVAL_PENDING, AccountStatus_from_str("REAPPROVAL_PENDING"));
    ASSERT_EQ(vp::AccountStatus::REJECTED, AccountStatus_from_str("REJECTED"));
    ASSERT_EQ(vp::AccountStatus::RESUBMITTED, AccountStatus_from_str("RESUBMITTED"));
    ASSERT_EQ(vp::AccountStatus::SIGNED_UP, AccountStatus_from_str("SIGNED_UP"));
    ASSERT_EQ(vp::AccountStatus::SUBMISSION_FAILED, AccountStatus_from_str("SUBMISSION_FAILED"));
    ASSERT_EQ(vp::AccountStatus::SUBMITTED, AccountStatus_from_str("SUBMITTED"));
}

TEST(AccountStatusTest, FromStringInvalid) {
    ASSERT_THROW(AccountStatus_from_str("invalid_status"), std::invalid_argument);
}

TEST(AccountStatusTest, IsAccountStatus) {
    ASSERT_TRUE(is_AccountStatus("ACCOUNT_CLOSED"));
    ASSERT_TRUE(is_AccountStatus("ACCOUNT_UPDATED"));
    ASSERT_TRUE(is_AccountStatus("ACTION_REQUIRED"));
    ASSERT_TRUE(is_AccountStatus("ACTIVE"));
    ASSERT_TRUE(is_AccountStatus("AML_REVIEW"));
    ASSERT_TRUE(is_AccountStatus("APPROVAL_PENDING"));
    ASSERT_TRUE(is_AccountStatus("APPROVED"));
    ASSERT_TRUE(is_AccountStatus("DISABLED"));
    ASSERT_TRUE(is_AccountStatus("DISABLE_PENDING"));
    ASSERT_TRUE(is_AccountStatus("EDITED"));
    ASSERT_TRUE(is_AccountStatus("INACTIVE"));
    ASSERT_TRUE(is_AccountStatus("KYC_SUBMITTED"));
    ASSERT_TRUE(is_AccountStatus("LIMITED"));
    ASSERT_TRUE(is_AccountStatus("ONBOARDING"));
    ASSERT_TRUE(is_AccountStatus("PAPER_ONLY"));
    ASSERT_TRUE(is_AccountStatus("REAPPROVAL_PENDING"));
    ASSERT_TRUE(is_AccountStatus("REJECTED"));
    ASSERT_TRUE(is_AccountStatus("RESUBMITTED"));
    ASSERT_TRUE(is_AccountStatus("SIGNED_UP"));
    ASSERT_TRUE(is_AccountStatus("SUBMISSION_FAILED"));
    ASSERT_TRUE(is_AccountStatus("SUBMITTED"));
    ASSERT_FALSE(is_AccountStatus("invalid_status"));
}
