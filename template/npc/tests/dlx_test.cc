#include "../../base/header.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../dlx.h"

using namespace testing;

void add_nodes(DancingLinks* dlx, vector<VI> a) {
    repn(i, len(a)) repn(j, len(a[i])) if (a[i][j]) dlx->add(i, j);
}

TEST(DancingLinks, Simple) {
    DancingLinks dlx(2, 2);
    dlx.add(0, 0);
    dlx.add(1, 1);
    int found = 0;
    dlx.solve([&](const vector<bool>& ans) {
        ++found;
        EXPECT_THAT(ans, ElementsAre(true, true));
        return true;
    });
    EXPECT_EQ(1, found);
}

TEST(DancingLinks, MultipleSolution) {
    DancingLinks dlx(2, 2);
    dlx.add(0, 0), dlx.add(0, 1);
    dlx.add(1, 0), dlx.add(1, 1);
    int found = 0;
    dlx.solve([&](const vector<bool>& ans) {
        ++found;
        EXPECT_THAT(ans,
                    AnyOf(ElementsAre(true, false), ElementsAre(false, true)));
        return true; // Continue searching.
    });
    EXPECT_EQ(2, found);

    found = 0;
    dlx.solve([&](const vector<bool>&) {
        ++found;
        return false; // Stop when found.
    });
    EXPECT_EQ(1, found);
}

TEST(DancingLinks, Big) {
    DancingLinks dlx(5, 5);
    add_nodes(&dlx, {{1, 0, 0, 0, 0},
                     {0, 1, 1, 0, 0},
                     {0, 1, 0, 0, 1},
                     {0, 0, 1, 1, 1},
                     {0, 1, 0, 0, 0}});
    int found = 0;
    dlx.solve([&](const vector<bool>& ans) {
        ++found;
        EXPECT_THAT(ans, ElementsAre(true, false, false, true, true));
        return true;
    });
    EXPECT_EQ(1, found);
}

TEST(DancingLinks, IgnoreColumns) {
    DancingLinks dlx(5, 5);
    add_nodes(&dlx, {{1, 1, 0, 0, 0},
                     {0, 0, 1, 1, 0},
                     {1, 1, 0, 1, 1},
                     {1, 0, 1, 1, 1},
                     {1, 0, 1, 0, 0}});
    int found = 0;
    dlx.solve([&](const vector<bool>&) {
        ++found;
        return true;
    });
    EXPECT_EQ(0, found);

    dlx.ignore(4);
    dlx.solve([&](const vector<bool>& ans) {
        ++found;
        EXPECT_THAT(ans, ElementsAre(true, true, false, false, false));
        return true;
    });
    EXPECT_EQ(1, found);
}

TEST(DancingLinks, PreChosen) {
    DancingLinks dlx(4, 3);
    add_nodes(&dlx, {{1, 1, 0}, {1, 0, 0}, {0, 1, 1}, {0, 0, 1}});
    int found = 0;
    dlx.solve([&](const vector<bool>&) {
        ++found;
        return true;
    });
    EXPECT_EQ(2, found);

    dlx.choose(0);
    found = 0;
    dlx.solve([&](const vector<bool>& ans) {
        ++found;
        EXPECT_THAT(ans, ElementsAre(true, false, false, true));
        return true;
    });
    EXPECT_EQ(1, found);
}

VI solve_nqueen(VI a) {
    const int n = len(a);
    DancingLinks dlx(n * n, n * 6);
    replr(y, n * 2, n * 6) dlx.ignore(y);
    repn(i, n) repn(j, n) {
        int x = i * n + j;
        if (a[i] == j) dlx.choose(x);
        dlx.add(x, i);
        dlx.add(x, n + j);
        dlx.add(x, n * 2 + (i + j));
        dlx.add(x, n * 4 + (i + n - j - 1));
    }
    VI r(n, -1);
    dlx.solve([&](const vector<bool>& ans) {
        repn(i, n) repn(j, n) if (ans[i * n + j]) r[i] = j;
        return false;
    });
    return r;
}

void check_nqueen(VI a) {
    const int n = len(a);
    repn(i, n) EXPECT_GE(a[i], 0);
    repn(i, n) replr(j, i + 1, n) {
        EXPECT_NE(a[i], a[j]);
        EXPECT_NE(i + a[i], j + a[j]);
        EXPECT_NE(i - a[i], j - a[j]);
    }
}

TEST(DancingLinks, NQueen) {
    check_nqueen(solve_nqueen({-1}));
    rep(n, 4, 50) check_nqueen(solve_nqueen(VI(n, -1)));
    check_nqueen(solve_nqueen({0}));
    check_nqueen(solve_nqueen({-1, 3, -1, -1}));
    check_nqueen(solve_nqueen({1, -1, -1, -1, 3, -1, -1, -1}));
}
