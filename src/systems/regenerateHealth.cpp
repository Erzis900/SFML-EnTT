#include "regenerateHealth.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/healthRegen.hpp"

namespace common::systems
{
    void regenerateHealth(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<common::components::health, common::components::maxHealth, common::components::healthRegen>();

        for (auto [entity, health, maxHealth, healthRegen] : view.each())
        {
            if (health.value > 0.f && health.value <= maxHealth.value)
            {
                registry.emplace<common::components::health>(entity, health.value + healthRegen.value * deltaTime);
            }
        }
    }
}
