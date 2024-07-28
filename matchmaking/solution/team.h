#pragma once

#include <nlohmann/json.hpp>

#include <array>

#include "user.h"

namespace team {
   enum class Side {
        kRed,
        kBlue,
        kError
    };

    // Side parser and serializer
    NLOHMANN_JSON_SERIALIZE_ENUM( Side, {
        {Side::kBlue, "blue"},
        {Side::kRed, "red"},
        {Side::kError, "error"}
    }) 
    
} // namespace Team


struct Team {
public:
    team::Side side;
    std::array<User, 5> users;

    // Team parser and serializer
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(Team, side, users)

};
