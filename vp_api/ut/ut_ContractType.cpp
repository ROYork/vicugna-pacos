#include <gtest/gtest.h>
#include "vp/ContractType.h"

TEST(ContractTypeTest, ToString) {
    ASSERT_EQ("call", to_str(vp::ContractType::call));
    ASSERT_EQ("put", to_str(vp::ContractType::put));
}

TEST(ContractTypeTest, FromString) {
    ASSERT_EQ(vp::ContractType::call, ContractType_from_str("call"));
    ASSERT_EQ(vp::ContractType::put, ContractType_from_str("put"));
}

TEST(ContractTypeTest, FromStringInvalid) {
    ASSERT_THROW(ContractType_from_str("invalid_contract_type"), std::invalid_argument);
}

TEST(ContractTypeTest, IsContractType) {
    ASSERT_TRUE(is_ContractType("call"));
    ASSERT_TRUE(is_ContractType("put"));
    ASSERT_FALSE(is_ContractType("invalid_contract_type"));
}
