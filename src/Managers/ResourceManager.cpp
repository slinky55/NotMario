#include "Managers/ResourceManager.h"

bool ResourceManager::LoadTexture(std::string_view _id,
                                  std::string_view _path)
{
    m_textures.emplace(_id, new sf::Texture());
    if (!m_textures[_id]->loadFromFile(_path.data()))
        return false;
    return true;
}

sf::Texture& ResourceManager::GetTexture(std::string_view _id)
{
    return *m_textures[_id];
}