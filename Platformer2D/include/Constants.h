#pragma once

#include "Math/Vector2.h"

constexpr float PIXELS_PER_METER {32.f};
constexpr float DAMPING_CONSTANT {0.3f};
constexpr float FRICTION_CONSTANT {0.3f};

const p2d::Vector2 UP_NORM {0.f, -1.f};
const p2d::Vector2 DOWN_NORM {0.f, 1.f};
const p2d::Vector2 GRAVITY {0.f, 9.8f};