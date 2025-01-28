#pragma once

#include "pch.hpp"

#include "components/children.hpp"
#include "components/modifiers.hpp"

namespace common::entities {
    constexpr std::size_t ATTRIBUTES_SIZE = 4;
    using Attributes = common::components::children<ATTRIBUTES_SIZE>;

    enum Stat : int { Health = 0, MaxHealth = 1, Speed = 2, Damage = 3 };

    entt::entity createAttribute(entt::registry &registry, Stat stat, float initialValue);
    entt::entity createModifier(entt::registry &registry, common::components::Scope scope, float value);
    entt::entity addModifier(entt::registry &registry, entt::entity attribute, common::components::Scope scope, float value);
}  // namespace common::entities