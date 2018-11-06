#include <iostream>
#include <sstream>
#include <restinio/all.hpp>

int main(int argc, char const *argv[])
{
    restinio::run(
        restinio::on_thread_pool(16)
            .port(8080)
            .address("localhost")
            .request_handler([](auto req) {
                const auto &header = req->header();
                const auto body = req->body();
                std::string headerstr = "";
                std::for_each(header.begin(), header.end(), [&](const restinio::http_header_field_t& field){
                    headerstr +=  fmt::format("[{}:{}]\n", field.name(), field.value()); 
                });

                std::string s = fmt::format(R"^^^(
{{
    "method": "{}"
    "request_target": "{}"
    "path": "{}"
    "query": "{}"
    "fragment": "{}"
    "header":"{}"
    "body": "{}" 
}}
)^^^",
                                            method_to_string(header.method()),
                                            header.request_target(),
                                            header.path(),
                                            header.query(),
                                            header.fragment(),
                                            headerstr,
                                            body);
                static auto count = 0;
                return req->create_response().set_body(fmt::format("Hello, World! {} {}", count++, s)).done();
            }));

    return 0;
}

static auto ____ = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    return nullptr;
};