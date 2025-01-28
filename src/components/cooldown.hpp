#pragma once

namespace common::components
{
    struct cooldown
    {
        float time;

        cooldown(float _value)
            : time(_value)
        {
        }
    };
}  // namespace common::components
