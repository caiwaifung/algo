#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../net.h"

using namespace testing;

TEST(Net, SimpleGraph) {
    Net<int> net(2);
    void* e0 = net.add(net.s(), 0, 3);
    void* e1 = net.add(net.s(), 1, 1);
    void* e2 = net.add(0, 1, 1);
    void* e3 = net.add(0, net.t(), 1);
    void* e4 = net.add(1, net.t(), 2);

    EXPECT_EQ(3, net.compute());

    EXPECT_EQ(2, net.flow(e0));
    EXPECT_EQ(1, net.flow(e1));
    EXPECT_EQ(1, net.flow(e2));
    EXPECT_EQ(1, net.flow(e3));
    EXPECT_EQ(2, net.flow(e4));

    EXPECT_FALSE(net.on_cut(e0));
    EXPECT_TRUE(net.on_cut(e1));
    EXPECT_TRUE(net.on_cut(e2));
    EXPECT_TRUE(net.on_cut(e3));
    EXPECT_FALSE(net.on_cut(e4));
    EXPECT_THAT(net.left(), ElementsAre(0));
}

TEST(Net, WithLowerBound) {
    Net<int> net(2);
    void* e0 = net.add(net.s(), 0, 2);
    void* e1 = net.add(net.s(), 1, 2);
    void* e2 = net.add(0, 1, {1, 2});
    void* e3 = net.add(0, net.t(), 2);
    void* e4 = net.add(1, net.t(), 2);

    EXPECT_EQ(3, net.compute());

    EXPECT_EQ(2, net.flow(e0));
    EXPECT_EQ(1, net.flow(e1));
    EXPECT_EQ(0, net.flow(e2));  // returns "amount above lower bound".
    EXPECT_EQ(1, net.flow(e3));
    EXPECT_EQ(2, net.flow(e4));
}

TEST(Net, ImpossibleLowerBound) {
    Net<int> net(2);
    net.add(net.s(), 0, 2);
    net.add(net.s(), 1, 2);
    net.add(0, 1, {3, 9});
    net.add(0, net.t(), 2);
    net.add(1, net.t(), 2);

    EXPECT_EQ(-1, net.compute());
}
