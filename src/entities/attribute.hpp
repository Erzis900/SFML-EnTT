#pragma once

#include "external/entt.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/speed.hpp"
#include "components/recalculate.hpp"
#include "components/modifiers.hpp"
#include "components/relationship.hpp"
#include "components/children.hpp"
#include "components/attribute.hpp"

namespace common::entities
{
    using Attributes = common::components::children<3>;

    enum Stat : int
    {
        Health = 0,
        MaxHealth = 1,
        Speed = 2
    };

    entt::entity createAttribute(entt::registry &registry, Stat stat, float initialValue);
    entt::entity createModifier(entt::registry &registry, common::components::Scope scope, float value);
    entt::entity addModifier(entt::registry &registry, entt::entity attribute, common::components::Scope scope, float value);
}