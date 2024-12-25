#ifndef UNIT_HPP
#define UNIT_HPP

namespace common::components
{
    struct unit
    {
        bool active;

        unit(bool _active) : active(_active) {}
    };
}

#endif // UNIT_HPP