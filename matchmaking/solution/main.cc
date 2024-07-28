#include <memory>
#include <string>

#include "request_manager.h"
#include "solver_mmr_greedy.h"
#include "solver_roles_greedy.h"
#include "solver.h"

// При локальном запуске http://server:8000 --> http://0.0.0.0:8000
int main(int argc, char** argv) {
    const int kTestAmount = 20;

    for(int test = 0; test < kTestAmount; test++) {
        RequestManager rm("test_" + std::to_string(test), "00000000-0000-0000-0000-000000000000", std::make_unique<RolesGreedySolver>());
        rm.Manage();
    }

    return 0;
}
