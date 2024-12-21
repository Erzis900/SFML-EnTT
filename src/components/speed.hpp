#ifndef SPEED_HPP
#define SPEED_HPP

namespace common::components
{
    struct speed
    {
        float value;

        // Parameterized constructor
        speed(float value) : value(value) {}
    };
}

#endif // SPEED_HPP