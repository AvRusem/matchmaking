#include <memory>
#include <string>

#include "request_manager.h"
#include "solver_mmr_greedy.h"
#include "solver_roles_greedy.h"
#include "solver.h"

int main(int argc, char** argv) {
    const int kTestAmount = 3;

    for(int test = 0; test < kTestAmount; test++) {
        RequestManager rm("test_" + std::to_string(test), "00000000-0000-0000-0000-000000000000", std::make_unique<RolesGreedySolver>());
        rm.Manage();
    }

    return 0;
}
