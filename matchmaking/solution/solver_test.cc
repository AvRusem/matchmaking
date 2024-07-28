#include "solver.h"

#include <gtest/gtest.h>

#include <vector>

#include "match.h"
#include "role.h"
#include "team.h"
#include "user.h"
#include "uuid_generator.h"

TEST(SolverTest, Algorithm) {
    std::cout << "LOL\n";

    User user{"", 0, {Role::kBot, Role::kJungle}, 100};

    std::vector<User> to_add(11);
    for(int i = 0; i < to_add.size(); i++) {
        user.user_id = uuid::Generate();
        user.mmr += 100;
        to_add[i] = user;
    }

    Solver solver;
    solver.AddUsers(to_add);
    auto res = solver();

    EXPECT_EQ(res.size(), 1);

    EXPECT_EQ(res[0].teams[0].side, team::Side::kRed);
    EXPECT_EQ(res[0].teams[1].side, team::Side::kBlue);

    EXPECT_EQ(res[0].teams[0].users[0].mmr, 100);
    EXPECT_EQ(res[0].teams[0].users[4].mmr, 500);
    EXPECT_EQ(res[0].teams[1].users[0].mmr, 600);
    EXPECT_EQ(res[0].teams[1].users[4].mmr, 1000);

    res = solver();
    EXPECT_TRUE(res.empty());
}
