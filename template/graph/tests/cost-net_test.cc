#include <gmock/gmock.h>
#include <gtest/gtest-death-test.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../cost-net.h"

using namespace testing;

TEST(CostNet, SimpleGraph) {
    CostNet<int> net(4);
    void* e0 = net.add(net.s(), 0, 2, 3);
    void* e1 = net.add(net.s(), 1, 2, 2);
    void* e2 = net.add(net.s(), 2, 2, 1);
    void* e3 = net.add(0, 3, 2, 2);
    void* e4 = net.add(1, 3, 2, 2);
    void* e5 = net.add(2, 3, 2, 2);
    void* e6 = net.add(3, net.t(), 3, 0);

    EXPECT_THAT(net.compute(), Pair(Eq(3), Eq(10)));

    EXPECT_EQ(0, net.flow(e0));
    EXPECT_EQ(1, net.flow(e1));
    EXPECT_EQ(2, net.flow(e2));
    EXPECT_EQ(0, net.flow(e3));
    EXPECT_EQ(1, net.flow(e4));
    EXPECT_EQ(2, net.flow(e5));
    EXPECT_EQ(3, net.flow(e6));
}

TEST(CostNet, NegativeEdgeIsBad) {
    CostNet<int> net(1);
    EXPECT_DEATH(net.add(net.s(), 0, 1, -1), "");
}
