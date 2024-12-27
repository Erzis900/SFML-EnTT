#pragma once

#include "pch.hpp"

namespace common::components
{
    struct shape
    {
        sf::CircleShape value;
        shape(sf::CircleShape _value) : value(_value) {}
    };
}