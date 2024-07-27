#pragma once

#include <vector>

#include "match.h"
#include "user.h"

class Solver {
public:
    Solver() = default;

    void AddUsers(const std::vector<User>& to_add);

    // operator() invoke Solve() and remove distributed users from not_distributed_users_
    const std::vector<Match> operator()(bool is_last = false);

protected:
    virtual std::vector<Match> Solve(bool is_last);

private:
    std::vector<User> not_distributed_users_;

};
