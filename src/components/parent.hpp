#ifndef PARENT_HPP
#define PARENT_HPP

#include "external/entt.hpp"

namespace common::components
{

    struct parent
    {
        entt::entity entity{entt::null};
    };
}

#endif // PARENT_HPP
