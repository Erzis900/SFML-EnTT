#pragma once
#include "pch.hpp"

namespace features::hitbox::components
{
    struct hitbox
    {
        float lifeSpan;
        float initialLifeSpan;
        float hitCount = 1;
        std::vector<entt::entity> entities = {};
    };
}
