#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>
#include <vector>

using Frame = sf::IntRect;

struct Animation
{
    sf::Texture& texture;

    std::vector<Frame> frames;

    uint32_t totalFrames {0};
    uint32_t currentFrame {0};
    uint32_t timer {0};
    uint32_t frameTime {0};

    bool play {false};
};

struct AnimationC
{
    std::unordered_map<std::string, Animation*> animations;
    Animation* currentAnimation;
};