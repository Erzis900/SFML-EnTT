#pragma once

namespace common::components {
    struct speed {
        float value;

        // Parameterized constructor
        speed(float value)
            : value(value)
        {
        }
    };
}  // namespace common::components
