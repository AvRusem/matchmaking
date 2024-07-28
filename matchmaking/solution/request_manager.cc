#include "request_manager.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
#include <vector>

#include "solver.h"
#include "user.h"
#include "match.h"

using json = nlohmann::json;

void RequestManager::Manage() {
    bool is_last_epoch = false;

    while(true) {
        // Get users from current epoch
        json data = SendGET();
        std::vector<User> new_users;
        data.get_to(new_users);

        // Use an algorithm to distribute users and organise matches
        solver_->AddUsers(data);
        std::vector<Match> new_matches = (*solver_)();
        data = new_matches;

        // Send matches to the server
        std::cout << data.dump(4);
        data = SendPOST(data, is_last_epoch);

        if(is_last_epoch)
            break;

        data.at("new_epoch").get_to(epoch_);
        data.at("is_last_epoch").get_to(is_last_epoch);
    }
}

json RequestManager::SendGET() const {
    auto r = cpr::Get(cpr::Url{url_ + "/matchmaking/users?test_name=" + test_name_ + "&epoch=" + epoch_});
    return json::parse(r.text);
}

json RequestManager::SendPOST(const json& data, bool is_last_epoch) const {
    auto r = cpr::Post(cpr::Url{url_ + "/matchmaking/match?test_name=" + test_name_ + "&epoch=" + epoch_},
                   cpr::Body{data.dump()},
                   cpr::Header{{"Content-Type", "application/json"}});
    
    json res;
    if(!is_last_epoch)
        res = json::parse(r.text);

    return res;
}
