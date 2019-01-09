#include <cereal/types/unordered_map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <fstream>

struct MyRecord
{
    uint8_t x, y;
    float z;

    template <class Archive>
    void serialize(Archive &ar)
    {
        ar(x, y, z);
    }
};

struct SomeData
{
    int32_t id;
    std::shared_ptr<std::unordered_map<uint32_t, MyRecord>> data;

    template <class Archive>
    void save(Archive &ar) const
    {
        ar(data);
    }

    template <class Archive>
    void load(Archive &ar)
    {
        static int32_t idGen = 0;
        id = idGen++;
        ar(data);
    }
};

int main(int argc, char const *argv[])
{
    {
        std::ofstream os("out.cereal", std::ios::binary);
        cereal::BinaryOutputArchive archive(os);

        SomeData myData;
        myData.data = std::make_shared<std::unordered_map<uint32_t, MyRecord>>();
        MyRecord r;
        r.x = 2;
        r.y = 3;
        r.z = 4.f;
        myData.data->insert_or_assign(1, r);
        archive(myData);
        SomeData myData2;
        myData2.data = myData.data;
        archive(myData2);
    }

    {
        std::ifstream is("out.cereal", std::ios::binary);
        cereal::BinaryInputArchive ar(is);
        SomeData myData;
        SomeData myData2;
        ar(myData);
        ar(myData2);
        auto &r = (*(myData.data))[1];
        std::cout << (int)r.x << std::endl
                  << (int)r.y << std::endl
                  << r.z << std::endl;
    }

    return 0;
}