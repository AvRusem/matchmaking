#include "solver_mmr_greedy.h"

#include <algorithm>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "functions.h"
#include "match.h"
#include "role.h"
#include "user.h"
#include "uuid_generator.h"

std::vector<Match> MMRGreedySolver::Solve(bool is_last) {
    std::vector<Match> result;

    if(!is_last)
        return result;
    
    std::vector<User> distributed_users = functions::DistributeMMRGreedy(not_distributed_users_);

    std::vector<Role> roles{Role::kTop, Role::kMid, Role::kBot, Role::kSup, Role::kJungle};
    std::vector<User> pair_of_users;
    std::unordered_map<std::string, int> uuid_to_index;
    for(int i = 1; i < distributed_users.size(); i += 2) {
        uuid_to_index[distributed_users[i].user_id] = i;

        std::vector<std::pair<int, Role>> top_roles;
        for(Role role : roles)
            top_roles.push_back({0, role});
        
        std::unordered_map<int, int> prior_to_points{
            {0, 3},
            {1, 5},
            {2, 8},
            {3, 13},
            {4, 21}
        };

        for(int j = 0; j < 2; j++) {
            for(int prior = 0; i < roles.size(); i++) {
                top_roles[static_cast<int>(distributed_users[i - j].roles[prior])].first += prior_to_points[prior];
            }    
        }
        std::sort(top_roles.begin(), top_roles.end());

        User users_pair = distributed_users[i];
        for(int prior = 0; prior < roles.size(); prior++) {
            users_pair.roles[i] = top_roles[i].second;
        }

        pair_of_users.push_back(users_pair);
    }

    distributed_users = functions::DistributeRolesGreedy(pair_of_users, roles);

    std::vector<std::vector<User>> users_pair_with_role(roles.size());
    for(auto& user : distributed_users) {
        users_pair_with_role[static_cast<int>(user.role)].push_back(user);
    }

    for(int ui = 0; ui < users_pair_with_role[0].size(); ui++) {
        Match match;
        match.match_id = uuid::Generate();

        Team red, blue;
        red.side = team::Side::kRed;
        blue.side = team::Side::kBlue;

        for(int ri = 0; ri < roles.size(); ri++) {
            red.users[ri] = users_pair_with_role[ri][ui];
            blue.users[ri] = distributed_users[uuid_to_index[users_pair_with_role[ri][ui].user_id] - 1];
            blue.users[ri].role = red.users[ri].role;

            if(ri % 2)
                std::swap(red.users[ri], blue.users[ri]);
        }

        match.teams[0] = red;
        match.teams[1] = blue;

        result.push_back(match);
    }

    return result;
}
