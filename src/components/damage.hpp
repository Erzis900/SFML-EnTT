#pragma once

namespace common::components
{
    struct damage
    {
        float value;

        // Parameterized constructor
        damage(float value)
            : value(value)
        {
        }
    };
}  // namespace common::components