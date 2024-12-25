#pragma once

#include "external/entt.hpp"

namespace common::components
{

    struct parent
    {
        entt::entity entity{entt::null};
    };
}
