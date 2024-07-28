#include "solver_mmr_greedy.h"

#include <vector>

#include "match.h"
#include "functions.h"

std::vector<Match> MMRGreedySolver::Solve(bool is_last) {
    std::vector<Match> result;

    if(!is_last)
        return result;
    
    std::vector<User> distributed_users = functions::DistributeMMRGreedy(not_distributed_users_);
    
}
