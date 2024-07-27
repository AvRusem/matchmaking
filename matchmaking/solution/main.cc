#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

#include <iostream>
#include <iomanip>
#include <memory>

#include "request_manager.h"
#include "solver.h"

using json = nlohmann::json;

// При локальном запуске http://server:8000 --> http://0.0.0.0:8000
int main(int argc, char** argv) {
    /*
    // Get request
    cpr::Response r = cpr::Get(cpr::Url{"http://server:8000/matchmaking/users?test_name=test_0&epoch=00000000-0000-0000-0000-000000000000"});
    std::cout << r.status_code << std::endl;                                            // 200
    std::cout << r.header["content-type"] << std::endl;                                 // application/json; charset=utf-8
    std::cout <<  std::setw(4) << json::parse(r.text).dump(4) << std::endl;             // JSON text string

    json request_body = json::parse(R"(
        {
            "example": 1
        }
    )");

    // Post request
    r = cpr::Post(cpr::Url{"http://server:8000/matchmaking/match?test_name=test_0&epoch=00000000-0000-0000-0000-000000000000"},
                   cpr::Body{request_body.dump()},
                   cpr::Header{{"Content-Type", "application/json"}});
    std::cout << r.status_code << std::endl;                                            // 200
    std::cout << r.header["content-type"] << std::endl;                                 // application/json; charset=utf-8
    std::cout <<  std::setw(4) << json::parse(r.text).dump(4) << std::endl;             // JSON text string
    */

   RequestManager rm("test_1", "00000000-0000-0000-0000-000000000000", std::unique_ptr<Solver>(new Solver));
   rm.Manage();

    return 0;
}
