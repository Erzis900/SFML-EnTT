#pragma once
#include <SFML/Graphics.hpp>

namespace common::components
{
    struct renderable
    {
        sf::CircleShape shape;
        float z = 1;
    };
}
