#include "user.h"

#include <nlohmann/json.hpp>

using json = nlohmann::json;

// Serializer
void to_json(json& j, const User& u) {
    j = json{{"id", u.user_id}, {"role", u.role}};
}

// Parser
void from_json(const json& j, User& u) {
    j.at("user_id").get_to(u.user_id);
    j.at("mmr").get_to(u.mmr);
    j.at("roles").get_to(u.roles);
    j.at("waitingTime").get_to(u.waiting_time);
}
