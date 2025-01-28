#pragma once

#include "pch.hpp"

namespace common::components
{
    template <std::size_t N> struct children
    {
        std::size_t size{};
        std::array<entt::entity, N> entities{};
    };
}  // namespace common::components
