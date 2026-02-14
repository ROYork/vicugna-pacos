#include <gtest/gtest.h>
#include "vp/NewsImageSize.h"

TEST(NewsImageSizeTest, ToString) {
    ASSERT_EQ("thumb", to_str(vp::NewsImageSize::thumb));
    ASSERT_EQ("small", to_str(vp::NewsImageSize::small));
    ASSERT_EQ("large", to_str(vp::NewsImageSize::large));
}

TEST(NewsImageSizeTest, FromString) {
    ASSERT_EQ(vp::NewsImageSize::thumb, NewsImageSize_from_str("thumb"));
    ASSERT_EQ(vp::NewsImageSize::small, NewsImageSize_from_str("small"));
    ASSERT_EQ(vp::NewsImageSize::large, NewsImageSize_from_str("large"));
}

TEST(NewsImageSizeTest, FromStringInvalid) {
    ASSERT_THROW(NewsImageSize_from_str("invalid_size"), std::invalid_argument);
}

TEST(NewsImageSizeTest, IsNewsImageSize) {
    ASSERT_TRUE(is_NewsImageSize("thumb"));
    ASSERT_TRUE(is_NewsImageSize("small"));
    ASSERT_TRUE(is_NewsImageSize("large"));
    ASSERT_FALSE(is_NewsImageSize("invalid_size"));
}
