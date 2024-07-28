#pragma once

#include "solver.h"

class RolesGreedySolver : public Solver {
protected:
    std::vector<Match> Solve(bool is_last) override final;

};
