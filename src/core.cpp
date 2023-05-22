#include "../include/core.h"

namespace Core
{
    std::map<std::string, unsigned> failed_attempts = {};
    dpp::cluster bot("");
    dpp::webhook wh("Place web-hook url here");

    namespace Util
    {
        std::list<std::string> readConfig(std::string file_name )
        {
            std::list<std::string> result_list;
            std::string line="";
            std::ifstream infile(file_name);
            while(std::getline(infile, line))
            {
                result_list.push_back(line);
            }

            return result_list;
        }

        unsigned check_domain(std::string domain)
        {
            unsigned result_code = 0;
            try
            {
                web::http::client::http_client client("https://" + domain);
                web::http::http_response response = client.request(web::http::methods::GET, "/").get();
                result_code = response.status_code();
                if (response.status_code() == 200)
                {
                    std::cout << domain << " is accessible" << std::endl;
                    failed_attempts[domain] = 0;
                }
                else
                {
                    throw std::runtime_error("bad response status");
                }
            }
            catch (const std::exception &ex)
            {
                std::cout << ex.what() << std::endl;
                std::cout << domain << " is not accessible" << std::endl;
                failed_attempts[domain] += 1;
                if (failed_attempts[domain] == 3)
                {
                    bot.execute_webhook(wh, dpp::message(domain + " is not accessible"));
                }
            }
            return result_code;
        }

        void check_domains(std::list<std::string> domains)
        {
            while (true)
            {
                std::cout << "Gathering domain responses in check_domain function" << std::endl;
                std::vector<std::future<unsigned>> result_vector;
                for (const std::string domain : domains)
                {
                    std::future<unsigned> result = std::async(std::launch::async, check_domain, domain);
                    result_vector.push_back(std::move(result));
                }

                for_each(result_vector.begin(), result_vector.end(), [](std::future<unsigned> &value)
                         { value.get(); });
                std::this_thread::sleep_for(std::chrono::seconds(5));
            }
        }
    }
}