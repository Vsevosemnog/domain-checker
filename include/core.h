#pragma once

#include <cpprest/http_client.h>
#include <dpp/dpp.h>

#include <string>
#include <list>
#include <fstream>
#include <vector>
#include <map>
#include <future>
#include <thread>
#include <chrono>

namespace Core
{
    extern std::map<std::string, unsigned> failed_attempts;
    extern dpp::cluster bot;
    extern dpp::webhook wh;

    namespace Util
    {
        std::list<std::string> readConfig(std::string file_name = "domain.conf");
        unsigned check_domain(std::string);
        void check_domains(std::list<std::string>);
    }
}