#ifndef RELATIONSHIP_HPP
#define RELATIONSHIP_HPP

#include <array>

#include "external/entt.hpp"

namespace common::components
{
    struct relationship
    {
        std::size_t children{};
        entt::entity first_child{entt::null};
        entt::entity prev{entt::null};
        entt::entity next{entt::null};
        entt::entity parent{entt::null};
    };
}

#endif // RELATIONSHIP_HPP
