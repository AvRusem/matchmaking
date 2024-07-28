#pragma once

#include <vector>

#include "role.h"
#include "user.h"

namespace functions {
    std::vector<User> DistributeMMRGreedy(std::vector<User>& users);
    std::vector<User> DistributeRolesGreedy(std::vector<User>& users, const std::vector<Role>& roles);

} // namespace functions

