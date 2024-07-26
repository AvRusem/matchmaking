#include "role.h"

#include <gtest/gtest.h>
#include <nlohmann/json.hpp>

#include <vector>

TEST(RoleTest, BasicParse) {
    auto j = R"(
        {
            "role": "bot"
        }
    )"_json;

    Role role = j["role"].template get<Role>();
    EXPECT_EQ(role, Role::kBot);
}

TEST(RoleTest, BasicSerialize) {
    Role role = Role::kMid;

    nlohmann::json j;
    j["role"] = role;
    EXPECT_EQ(j["role"], "mid");
}

TEST(RoleTest, ArrayParse) {
    auto j = R"(
        {
            "roles": ["top", "mid", "bot", "sup", "jungle"]
        }
    )"_json;

    std::vector<Role> roles = j["roles"].template get<std::vector<Role>>();
    EXPECT_EQ(roles[2], Role::kBot);
}

TEST(RoleTest, ArraySerialize) {
    std::vector<Role> roles = std::vector<Role>{Role::kTop, Role::kMid};

    nlohmann::json j;
    j["roles"] = roles;
    EXPECT_EQ(j["roles"][1], "mid");
    EXPECT_EQ(j["roles"][0], "top");
}
