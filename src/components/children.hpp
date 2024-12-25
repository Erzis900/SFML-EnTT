#ifndef CHILDREN_HPP
#define CHILDREN_HPP

#include <array>

#include "external/entt.hpp"

namespace common::components
{
    template <std::size_t N>
    struct children
    {
        std::size_t size{};
        std::array<entt::entity, N> entities{};
    };
}

#endif // CHILDREN_HPP
