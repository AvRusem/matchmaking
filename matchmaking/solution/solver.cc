#include "solver.h"

#include <algorithm>
#include <unordered_set>
#include <vector>

#include "match.h"
#include "team.h"
#include "user.h"
#include "uuid_generator.h"

void Solver::AddUsers(const std::vector<User>& to_add) {
    not_distributed_users_.insert(not_distributed_users_.end(), to_add.cbegin(), to_add.cend());
}

const std::vector<Match> Solver::operator()(bool is_last) {
    const std::vector<Match> result = Solve(is_last);

    // Get distributed user's uuids
    std::unordered_set<std::string> uuid_to_remove;
    for(const auto& match : result) {
        for(const auto& team : match.teams) {
            for(const auto& user : team.users) {
                uuid_to_remove.insert(user.user_id);
            }
        }
    }

    // Erase distributed user's from not_distributed_users_
    not_distributed_users_.erase(std::remove_if(not_distributed_users_.begin(), not_distributed_users_.end(),
                                [&uuid_to_remove](const User& u) {
                                    return uuid_to_remove.count(u.user_id);
                                }), not_distributed_users_.end());

    return result;
}

std::vector<Match> Solver::Solve(bool is_last) {
    std::vector<Match> result;

    // Just sort by mmr and select in order
    std::sort(not_distributed_users_.begin(), not_distributed_users_.end(),
             [](const User& a, const User& b) {
                return a.mmr < b.mmr;
             });
    
    for(int mi = 0; mi < not_distributed_users_.size() / 10; mi++) {
        Match match;
        for(int ti = 0; ti < match.teams.size(); ti++) {
            Team team;
            for(int ui = 0; ui < team.users.size(); ui++) {
                team.users[ui] = not_distributed_users_[mi * 10 + ti * 5 + ui];
                team.users[ui].role = team.users[ui].roles[0];
            }

            team.side = team::Side::kRed;
            if(ti == 1)
                team.side = team::Side::kBlue;
            
            match.teams[ti] = team;
        }

        match.match_id = uuid::Generate();
        result.push_back(match);
    }

    return result;
}
