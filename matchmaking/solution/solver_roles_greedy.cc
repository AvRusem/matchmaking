#include "solver_roles_greedy.h"

#include <algorithm>
#include <vector>

#include "functions.h"
#include "match.h"
#include "role.h"
#include "team.h"
#include "uuid_generator.h"

std::vector<Match> RolesGreedySolver::Solve(bool is_last) {
    std::vector<Match> result;

    if(!is_last || not_distributed_users_.size() < 10)
        return result;
    
    std::vector<Role> roles{Role::kTop, Role::kMid, Role::kBot, Role::kSup, Role::kJungle};
    std::vector<User> distributed_users = functions::DistributeRolesGreedy(not_distributed_users_, roles);

    std::vector<std::vector<User>> users_with_role(roles.size());
    for(auto& user : distributed_users) {
        users_with_role[static_cast<int>(user.role)].push_back(user);
    }
    for(int i = 0; i < roles.size(); i++) {
        std::sort(users_with_role[i].begin(), users_with_role[i].end(),
                  [](const User& a, const User& b) {
                    return a.mmr < b.mmr;
                  });
    }

    for(int ui = 1; ui < users_with_role[0].size(); ui++) {
        Match match;
        match.match_id = uuid::Generate();

        Team red, blue;
        red.side = team::Side::kRed;
        blue.side = team::Side::kBlue;

        for(int ri = 0; ri < roles.size(); ri++) {
            red.users[ri] = users_with_role[ri][ui - 1];
            blue.users[ri] = users_with_role[ri][ui];

            if(ri % 2)
                std::swap(red.users[ri], blue.users[ri]);
        }

        match.teams[0] = red;
        match.teams[1] = blue;

        result.push_back(match);
    }

    return result;
}
