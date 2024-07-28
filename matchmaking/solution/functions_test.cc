#include "functions.h"

#include <gtest/gtest.h>

#include <vector>

#include "role.h"
#include "user.h"

TEST(FunctionsTest, DistributeMMRGreedy11) {
    std::vector<int> mmrs{1, 2, 3, 4, 5, 16, 17, 18, 19, 20, 21};

    std::vector<User> users(mmrs.size());
    for(int i = 0; i < users.size(); i++)
        users[i].mmr = mmrs[i];
    
    std::vector<User> result = functions::DistributeMMRGreedy(users);

    EXPECT_EQ(result.size(), 10);

    int dif = 0;
    for(int i = 1; i < result.size(); i += 2)
        dif += result[i].mmr - result[i - 1].mmr;
    EXPECT_EQ(dif, 5);
}

TEST(FunctionsTest, DistributeMMRGreedy10) {
    std::vector<int> mmrs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<User> users(mmrs.size());
    for(int i = 0; i < users.size(); i++)
        users[i].mmr = mmrs[i];
    
    std::vector<User> result = functions::DistributeMMRGreedy(users);

    EXPECT_EQ(result.size(), 10);

    int dif = 0;
    for(int i = 1; i < result.size(); i += 2)
        dif += result[i].mmr - result[i - 1].mmr;
    EXPECT_EQ(dif, 5);
}

TEST(FunctionsTest, DistributeMMRGreedy19) {
    std::vector<int> mmrs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    std::vector<User> users(mmrs.size());
    for(int i = 0; i < users.size(); i++)
        users[i].mmr = mmrs[i];
    
    std::vector<User> result = functions::DistributeMMRGreedy(users);

    EXPECT_EQ(result.size(), 10);

    int dif = 0;
    for(int i = 1; i < result.size(); i += 2)
        dif += result[i].mmr - result[i - 1].mmr;
    EXPECT_EQ(dif, 5);
}

TEST(FunctionsTest, DistributeMMRGreedy20) {
    std::vector<int> mmrs{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};

    std::vector<User> users(mmrs.size());
    for(int i = 0; i < users.size(); i++)
        users[i].mmr = mmrs[i];
    
    std::vector<User> result = functions::DistributeMMRGreedy(users);

    EXPECT_EQ(result.size(), 20);

    int dif = 0;
    for(int i = 1; i < result.size(); i += 2)
        dif += result[i].mmr - result[i - 1].mmr;
    EXPECT_EQ(dif, 10);
}

TEST(FunctionsTest, DistributeRolesGreedy) {
    std::vector<Role> roles{Role::kTop, Role::kMid, Role::kBot, Role::kSup, Role::kJungle};

    std::vector<User> users(11);
    for(int i = 0; i < users.size(); i++) {
        users[i].roles = roles;
    }

    std::vector<User> result = functions::DistributeRolesGreedy(users, roles);

    EXPECT_EQ(result.size(), 10);

    for(Role role : roles) {
        EXPECT_EQ(result[static_cast<int>(role) * 2].role, role);
        EXPECT_EQ(result[static_cast<int>(role) * 2 + 1].role, role);
    }
}
