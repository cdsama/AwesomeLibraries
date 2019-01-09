#include <restinio/all.hpp>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main(int argc, char const *argv[])
{
    restinio::run(
        restinio::on_thread_pool(16)
            .port(8080)
            .address("0.0.0.0")
            .request_handler([](auto req) {
                const auto &header = req->header();
                json j;
                static auto world = 0;
                j["hello"] = world++;
                j["method"] = method_to_string(header.method());
                j["request_target"] = header.request_target();
                j["path"] = header.path();
                j["query"] = header.query();
                j["fragment"] = header.fragment();
                std::for_each(header.begin(), header.end(), [&](const auto &field) {
                    j["header_fields"][field.name()] = field.value();
                });
                j["body"] = req->body();
                return req->create_response()
                    .append_header_date_field()
                    .append_header(restinio::http_field::content_type, "text/json; charset=utf-8")
                    .set_body(j.dump())
                    .done();
            }));

    return 0;
}