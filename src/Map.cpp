#include <Map.h>

void Map::Parse(const std::string& _mapname,
                uint32_t _layerCount)
{
    std::ifstream in {};

    for (uint32_t i = 0; i < _layerCount; i++)
    {
        auto& layer = m_layers.emplace_back();

        in.open("../../../res/maps/" + _mapname + "/" + _mapname + "_" + std::to_string(i) + ".map");

        std::string line, num;
        std::vector<int> row;

        while (std::getline(in, line))
        {
            row.clear();
            std::stringstream ss {line};
            while (std::getline(ss, num, ','))
            {
                row.push_back(std::stoi(num));
            }
            layer.push_back(row);
        }

        in.close();
    }
}
