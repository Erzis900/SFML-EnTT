#pragma once

#include "external/entt.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/speed.hpp"
#include "components/recalculate.hpp"
#include "components/modifiers.hpp"
#include "components/relationship.hpp"

namespace common::entities
{
    inline constexpr std::size_t ATTRIBUTES_COUNT = 3;

    enum class Stat : int
    {
        Health = 0,
        MaxHealth = 1,
        Speed = 2
    };

    entt::entity createAttribute(entt::registry &registry, Stat stat, float initialValue);
    entt::entity createModifier(entt::registry &registry, common::components::Scope scope, float value);
    entt::entity addModifier(entt::registry &registry, entt::entity attribute, common::components::Scope scope, float value);
}