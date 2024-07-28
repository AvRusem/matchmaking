#pragma once

#include "solver.h"

class TimeGreedySolver : public Solver {
protected:
    std::vector<Match> Solve(bool is_last) override final;

};
