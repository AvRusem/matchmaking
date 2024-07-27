#include "request_manager.h"

#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>

#include "solver.h"

using json = nlohmann::json;

void RequestManager::Manage() {
    bool is_last_epoch = false;
    while(true) {
        json data;
        json j = SendPOST(data, is_last_epoch);

        if(is_last_epoch)
            break;

        j.at("new_epoch").get_to(epoch_);
        j.at("is_last_epoch").get_to(is_last_epoch);
        std::cout << epoch_ << '\n';
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
