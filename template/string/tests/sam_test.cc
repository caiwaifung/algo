#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "../../base/header.h"
#include "../sam.h"

using namespace testing;

TEST(SAM, Occurrences) {
    SAM<int> sam;
    for (int ch : {1, 2, 1, 3, 1, 2, 3, 4}) {
        sam.extend(ch);
    }
    sam.finish();
    for (auto* cur : sam.states_top_down()) {
        cur->info = cur->is_end;
    }
    for (auto* cur : sam.states_bottom_up()) {
        if (cur->f) {
            cur->f->info += cur->info;
        }
    }

    // Occurrence of "1".
    EXPECT_THAT(sam.root()->succ[1]->info, Eq(3));

    // Occurrence of "12".
    EXPECT_THAT(sam.root()->succ[1]->succ[2]->info, Eq(2));

    // Occurrence of "21".
    EXPECT_THAT(sam.root()->succ[2]->succ[1]->info, Eq(1));

    // Occurrence of "12131234".
    EXPECT_THAT(sam.root()
                    ->succ[1]
                    ->succ[2]
                    ->succ[1]
                    ->succ[3]
                    ->succ[1]
                    ->succ[2]
                    ->succ[3]
                    ->succ[4]
                    ->info,
                Eq(1));

    // Occurrence of "124" is zero.
    EXPECT_THAT(sam.root()->succ[1]->succ[2]->succ[4], IsNull());
}

TEST(SAM, MinimalRepresentation) {
    const VI str = {2, 1, 3, 2, 1, 3, 2};
    SAM<char> sam;
    for (int ch : str) sam.extend(ch);
    for (int ch : str) sam.extend(ch);

    VI ans;
    auto cur = sam.root();
    repn(i, len(str)) {
        int ch = 0;
        while (!cur->succ[ch]) ++ch;
        ans.pb(ch), cur = cur->succ[ch];
    }
    EXPECT_THAT(ans, ElementsAre(1, 3, 2, 1, 3, 2, 2));
}
