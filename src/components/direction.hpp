#ifndef DIRECTION_HPP
#define DIRECTION_HPP

namespace common::components
{
    struct direction
    {
        float x;
        float y;
        direction(float dx = 0.f, float dy = 0.f) : x(dx), y(dy) {}
    };
}

#endif // DIRECTION_HPP