#pragma once

#include <nlohmann/json.hpp>

#include <array>
#include <string>

#include "team.h"

struct Match {
public:
    std::string match_id;
    std::array<Team, 2> teams;

    // Match parser and serializer
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Match, match_id, teams)

};
