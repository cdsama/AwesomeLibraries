#define CPPHTTPLIB_OPENSSL_SUPPORT 1
#include "httplib.h"
#include <iostream>

int main(void)
{
    httplib::SSLClient cli("raw.githubusercontent.com", 443);

    auto res = cli.Get("/asgrim/year/master/en/currentYear");
    if (res && res->status == 200)
    {
        std::cout << res->body << std::endl;
    }
}