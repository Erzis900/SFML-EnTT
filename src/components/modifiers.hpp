#pragma once

#include "external/entt.hpp"
#include <array>

namespace common::components
{
    enum Scope : int
    {
        Flat = 100,
        PercentAdd = 200,
        PercentMult = 300,
        Set = 400,
    };

    struct modifier
    {
        float value;
        Scope scope;
    };
}
