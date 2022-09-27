#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string_view>

#include <SFML/Graphics.hpp>

enum class TileType {
    TRANSPARENT = -1,
    BACKGROUND = 255,
    ROCK_GROUND_LEFT = 10,
    ROCK_GROUND_MIDDLE = 11,
    ROCK_GROUND_RIGHT = 12,
    ROCK_WALL_LEFT = 27,
    DIRT_MIDDLE = 28,
    ROCK_WALL_RIGHT = 29,
    CHEST_CLOSED = 82,
    SIGN_DARK_RIGHT = 32
};

struct TileProperties
{
    sf::Texture& tex;   // Whole texture sheet
    sf::IntRect rect;   // Part of the texture that will be rendered
    sf::Vector2f size;
};

using TileSet = std::unordered_map<TileType, TileProperties*>;
using MapLayer = std::vector<std::vector<int>>;

struct Map
{
    TileSet tileset;
    std::vector<MapLayer> layers;
    uint32_t numLayers {0};
};


inline void ParseMapData(const std::string& _mapname,
              Map& _map)
{
    for (int i = _map.numLayers - 1; i >= 0; i--)
    {
        auto& layer = _map.layers.emplace_back();

        std::ifstream in {"../res/maps/" + _mapname + "/" + _mapname + "_" + std::to_string(i) + ".csv"};

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
    }
}