#include "match.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include "team.h"
#include "user.h"

TEST(MatchTest, BasicSerialize) {
    User user{"4877bf28-68a8-4f6c-84a8-707223e9237b", 2000, {Role::kTop, Role::kMid}, 12, Role::kMid};

    Team team1;
    team1.side = team::Side::kRed;
    for(int i = 0; i < team1.users.size(); i++)
        team1.users[i] = user;
    
    Team team2;
    team2.side = team::Side::kBlue;
    for(int i = 0; i < team2.users.size(); i++)
        team2.users[i] = user;

    Match match{"4877bf28-68a8-4f6c-84a8-707223e9237b", {team1, team2}};

    nlohmann::json j = match;
    auto j_expected = R"(
        {
            "match_id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
            "teams": [
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
                },
                {
                    "side": "blue",
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
            ]
        }
    )"_json;

    EXPECT_EQ(j, j_expected);
}
