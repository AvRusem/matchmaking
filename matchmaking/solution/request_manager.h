#pragma once

#include <nlohmann/json.hpp>

#include <memory>
#include <string>

#include "solver.h"

using json = nlohmann::json;

class RequestManager {
public:
    RequestManager() = default;
    RequestManager(const std::string& test_name, const std::string& epoch, std::unique_ptr<Solver> solver) :
                    test_name_(test_name), epoch_(epoch), solver_(solver.release()) {
        url_ = "http://server:8000";

        #ifdef BUILD_LOCAL
            url_ = "http://0.0.0.0:8000";
        #endif
    }

    void Manage();

private:
    std::string epoch_;
    std::string test_name_;
    std::string url_;

    std::unique_ptr<Solver> solver_;

    json SendGET() const;
    json SendPOST(const json& data, bool is_last_epoch) const;

};
