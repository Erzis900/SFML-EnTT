#ifndef COOLDOWN_HPP
#define COOLDOWN_HPP

namespace common::components
{
    struct cooldown
    {
        float time;

        cooldown(float _value) : time(_value) {}
    };
}

#endif // COOLDOWN_HPP