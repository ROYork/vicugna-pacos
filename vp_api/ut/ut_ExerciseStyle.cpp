#include <gtest/gtest.h>
#include "vp/ExerciseStyle.h"

TEST(ExerciseStyleTest, ToString) {
    ASSERT_EQ("american", to_str(vp::ExerciseStyle::american));
    ASSERT_EQ("european", to_str(vp::ExerciseStyle::european));
}

TEST(ExerciseStyleTest, FromString) {
    ASSERT_EQ(vp::ExerciseStyle::american, ExerciseStyle_from_str("american"));
    ASSERT_EQ(vp::ExerciseStyle::european, ExerciseStyle_from_str("european"));
}

TEST(ExerciseStyleTest, FromStringInvalid) {
    ASSERT_THROW(ExerciseStyle_from_str("invalid_style"), std::invalid_argument);
}

TEST(ExerciseStyleTest, IsExerciseStyle) {
    ASSERT_TRUE(is_ExerciseStyle("american"));
    ASSERT_TRUE(is_ExerciseStyle("european"));
    ASSERT_FALSE(is_ExerciseStyle("invalid_style"));
}
