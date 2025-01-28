#pragma once

#include "pch.hpp"

namespace common::components {
    struct renderable {
        sf::CircleShape shape;
        float z = 1;
    };
}  // namespace common::components
