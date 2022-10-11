#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <string_view>
#include <cstdint>

#include <SFML/Graphics.hpp>

enum TileType
{
    TRANSPARENT = -1,
    COIN_BLOCK_ACTIVE = 114,
    FLOOR = 96,
    PIPE_UP = 0,
    BRICK = 97
};

struct TileProperties
{
    sf::Texture& tex;   // Whole texture sheet
    sf::IntRect rect;   // Part of the texture that will be rendered
    sf::Vector2f size;  // Size of the tile, used for collider

    bool doesCollide {false};
};

using TileSet = std::unordered_map<TileType, TileProperties*>;
using MapLayer = std::vector<std::vector<int>>;

class Map
{
public:
    Map() = default;

    /*
     * API
     */
    void Parse(const std::string& _mapName,
               uint32_t _layerCount);

//
//    void AddTile(std::string_view _id,
//                 TileProperties* _properties);

private:
    TileSet m_tileset;
    std::vector<MapLayer> m_layers;
    uint32_t m_layerCount {0};
};