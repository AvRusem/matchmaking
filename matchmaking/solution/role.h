#pragma once

#include <nlohmann/json.hpp>

enum class Role {
    kTop,
    kMid,
    kBot,
    kSup,
    kJungle,
    kError
};

// Role parser and serializer
NLOHMANN_JSON_SERIALIZE_ENUM( Role, {
    {Role::kTop, "top"},
    {Role::kMid, "mid"},
    {Role::kBot, "bot"},
    {Role::kSup, "sup"},
    {Role::kJungle, "jungle"},
    {Role::kError, "error"}
})
