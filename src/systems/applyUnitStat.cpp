#include "applyUnitStat.hpp"
#include <iostream>
#include "components/unit.hpp"
#include "components/children.hpp"
#include "components/speed.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/attribute.hpp"
#include "entities/attribute.hpp"

namespace common::systems
{
    void applyUnitStat(entt::registry &registry)
    {
        common::systems::applyUnitSpeed(registry);
        common::systems::applyUnitHealth(registry);
    }

    void applyUnitSpeed(entt::registry &registry)
    {
        auto view = registry.view<common::components::unit, common::entities::Attributes, common::components::speed>();

        for (auto [entity, unit, children, speed] : view.each())
        {
            auto &child_speed = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Speed]);
            registry.replace<common::components::speed>(entity, child_speed.value);
        }
    }

    void applyUnitHealth(entt::registry &registry)
    {
        auto view = registry.view<common::components::unit, common::entities::Attributes, common::components::health, common::components::maxHealth>();

        for (auto [entity, unit, children, health, maxHealth] : view.each())
        {
            auto &health = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Health]);
            auto &maxHealth = registry.get<common::components::attribute>(children.entities[common::entities::Stat::MaxHealth]);
            registry.replace<common::components::health>(entity, health.value);
            registry.replace<common::components::maxHealth>(entity, maxHealth.value);
        }
    }
}