#pragma once

#include <unordered_map>
#include <string_view>

#include <SFML/Graphics/Texture.hpp>

class ResourceManager
{
public:
    ResourceManager() = default;

    [[nodiscard]] bool LoadTexture(std::string_view _id,
                                   std::string_view _path);
    sf::Texture& GetTexture(std::string_view _id);

private:
    std::unordered_map<std::string_view, sf::Texture*> m_textures;
};