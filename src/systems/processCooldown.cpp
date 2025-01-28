#include "processCooldown.hpp"
#include "components/cooldown.hpp"

namespace common::systems {
    void processCooldown(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<common::components::cooldown>();

        for (auto [entity, cd] : view.each())
        {
            if (cd.time <= 0)
            {
                registry.remove<common::components::cooldown>(entity);
            }
            else
            {
                registry.replace<common::components::cooldown>(entity, cd.time - deltaTime);
            }
        }
    }
}  // namespace common::systems
