#include "team.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "user.h"

TEST(TeamTest, BasicSerialize) {
    User user{"4877bf28-68a8-4f6c-84a8-707223e9237b", 2000, {Role::kTop, Role::kMid}, 12, Role::kMid};

    Team team;
    team.side = team::Side::kRed;
    for(int i = 0; i < team.users.size(); i++)
        team.users[i] = user;

    nlohmann::json j = team;
    auto j_expected = R"(
        {
            "side": "red",
            "users": [
                {
                    "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
                    "role": "mid"
                },
                {
                    "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
                    "role": "mid"
                },
                {
                    "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
                    "role": "mid"
                },
                {
                    "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
                    "role": "mid"
                },
                {
                    "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
                    "role": "mid"
                }
            ]
        }
    )"_json;

    EXPECT_EQ(j, j_expected);
}
