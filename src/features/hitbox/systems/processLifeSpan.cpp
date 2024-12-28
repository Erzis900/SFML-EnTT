#include "processLifespan.hpp"
#include "../components/hitbox.hpp"

namespace features::hitbox::systems
{
    void processLifeSpan(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<features::hitbox::components::hitbox>();

        for (auto [entity, hitbox] : view.each())
        {
            hitbox.lifeSpan -= deltaTime;

            if (hitbox.lifeSpan <= 0)
            {
                registry.destroy(entity);
            }
        }
    }
}
