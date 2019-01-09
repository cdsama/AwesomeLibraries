#include <chaiscript/chaiscript.hpp>

int main(int argc, char const *argv[])
{
    chaiscript::ChaiScript chai;
    chai.eval(R"chaiscript(
        print("hello world!")
        )chaiscript");
    return 0;
}
