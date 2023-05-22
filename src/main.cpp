#include "../include/domain-checker.h"

int main(int argc, char** argv) 
{
    std::list<std::string> domains = Core::Util::readConfig();
    Core::Util::check_domains(domains);

    (void)argc;
    (void)argv;
    return 0;
}