#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../hash.h"

class HashTest : public testing::Test {
protected:
    HashTest() {
        // Hash needs initialization.
        Hash::init(1000);
    }
};

TEST_F(HashTest, Eq) {
    EXPECT_TRUE(Hash(5) == Hash(5));
    EXPECT_TRUE(Hash(5) + Hash(6) == Hash(5) + Hash(6));
    EXPECT_FALSE(Hash(5) == Hash(7));
    EXPECT_FALSE(Hash(5) + Hash(6) == Hash(7) + Hash(6));
    EXPECT_FALSE(Hash(5) + Hash(6) == Hash(5));
    EXPECT_FALSE(Hash(5) + Hash(6) == Hash(6));
}

TEST_F(HashTest, Associativity) {
    EXPECT_EQ((Hash(1) + Hash(2)) + Hash(3), Hash(1) + (Hash(2) + Hash(3)));
}

TEST_F(HashTest, RemoveLeftPart) {
    const Hash h1 = Hash(1) + Hash(2) + Hash(3);
    const Hash h2 = Hash(1) + Hash(2);
    const Hash h3 = Hash(3);
    EXPECT_EQ(h3, h1.remove_l(h2));
}

TEST_F(HashTest, RemoveRightPart) {
    const Hash h1 = Hash(1) + Hash(2) + Hash(5);
    const Hash h2 = Hash(2) + Hash(5);
    const Hash h3 = Hash(1);
    EXPECT_EQ(h3, h1.remove_r(h2));
}
