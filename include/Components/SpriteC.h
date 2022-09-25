#pragma once

#include <memory>

#include <SFML/Graphics/Sprite.hpp>

struct RenderableC
{
    std::shared_ptr<sf::Sprite> sprite;
};

