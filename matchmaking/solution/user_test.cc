#include "user.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <vector>

#include "role.h"

TEST(UserTest, BasicParse) {
    auto j = R"(
        {
            "user_id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
            "mmr": 2000,
            "roles": ["top", "mid", "bot", "sup", "jungle"],
            "waitingTime": 12
        }
    )"_json;

    User user = j.template get<User>();
    EXPECT_EQ(user.user_id, "4877bf28-68a8-4f6c-84a8-707223e9237b");
    EXPECT_EQ(user.mmr, 2000);
    EXPECT_EQ(user.roles[2], Role::kBot);
    EXPECT_EQ(user.waiting_time, 12);
}

TEST(UserTest, BasicSerialize) {
    User user{"4877bf28-68a8-4f6c-84a8-707223e9237b", 2000, {Role::kTop, Role::kMid}, 12, Role::kMid};

    auto j = user;
    auto j_expected = R"(
        {
            "id": "4877bf28-68a8-4f6c-84a8-707223e9237b",
            "role": "mid"
        }
    )"_json;

    EXPECT_EQ(j, j_expected);
}
