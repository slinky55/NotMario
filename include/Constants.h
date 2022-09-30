#pragma once

constexpr float PIXELS_PER_METER {32.f};
constexpr float DAMPING_CONSTANT {0.3f};
constexpr float FRICTION_CONSTANT {0.1f};

constexpr sf::Vector2f UP_NORM {0.f, -1.f};
constexpr sf::Vector2f DOWN_NORM {0.f, 1.f};
constexpr sf::Vector2f GRAVITY {0.f, 9.8f};