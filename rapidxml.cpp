#include <iostream>
#include <fstream>
#include <rapidxml.hpp>
#include <rapidxml_utils.hpp>
#include <fmt/format.h>
int main(int argc, char const *argv[])
{
    rapidxml::file<> xmlFile("leetcode.xml");
    rapidxml::xml_document<> doc;
    doc.parse<0>(xmlFile.data());

    if (auto body = doc.first_node(); body != nullptr)
    {
        auto count = 0;
        for (auto problem = body->first_node(); problem != nullptr; problem = problem->next_sibling())
        {
            auto status = problem->first_node();
            auto id = status->next_sibling();
            auto title = id->next_sibling();
            auto solution = title->next_sibling();
            auto acceptance = solution->next_sibling();
            auto difficulty = acceptance->next_sibling();
            bool ac = false;
            if (auto attr = status->first_attribute("value"); attr != nullptr && attr->value() == std::string("ac"))
            {
                ac = true;
            }
            int id_number = std::stoi(id->value());
            std::string title_str = title->first_attribute("value")->value();
            std::string title_link_str = title->first_node()->first_node()->first_attribute("href")->value();
            title_link_str = title_link_str.substr(10);
            std::string difficulty_str = difficulty->first_node()->value();
            std::cout << fmt::format("{}add_problem({:04}{:^8} {}) # {}", ac ? "" : "#", id_number, difficulty_str, title_link_str, title_str) << std::endl;
        }
    }
    else
    {
        std::cout << "error" << std::endl;
    }

    return 0;
}
