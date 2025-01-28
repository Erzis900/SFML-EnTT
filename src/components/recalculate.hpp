#pragma once

namespace common::components
{
    struct recalculate
    {
        bool value;
        recalculate(bool recalc)
            : value(recalc)
        {
        }
    };
}  // namespace common::components