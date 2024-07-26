#pragma once

#include <nlohmann/json.hpp>

#include <string>
#include <vector>

#include "role.h"

using json = nlohmann::json;

struct User {
public:
    std::string user_id;
    int mmr;
    std::vector<Role> roles;
    int waiting_time;

    Role role = Role::kError;

};

// User parser and serializer
void to_json(json& j, const User& u);
void from_json(const json& j, User& u);
