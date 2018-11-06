#include <crow.h>

int main(int argc, char const *argv[])
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([]() {
        return "Hello world";
    });

    CROW_ROUTE(app, "/json")
    ([] {
        crow::json::wvalue x;
        x["message"] = "Hello, World!";
        return x;
    });

    CROW_ROUTE(app, "/add_json")
        .methods("POST"_method)([](const crow::request &req) {
            auto x = crow::json::load(req.body);
            if (!x)
                return crow::response(400);
            int sum = x["a"].i() + x["b"].i();
            crow::json::wvalue v;
            v["value"] = sum;
            return crow::response{v};
        });

    app.port((uint16_t)18080).multithreaded().run();

    return 0;
}