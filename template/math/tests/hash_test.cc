#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../hash.h"

TEST(Hash, Eq) {
    EXPECT_TRUE(Hash(5) == Hash(5));
    EXPECT_FALSE(Hash(5) == Hash(7));
}
