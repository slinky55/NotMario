#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

struct RenderableC
{
    std::shared_ptr<sf::Drawable> drawable;
};

