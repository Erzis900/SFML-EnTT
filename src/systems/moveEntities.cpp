#include "systems/moveEntities.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "components/direction.hpp"

namespace systems
{
    void moveEntities(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<components::position, components::speed, components::direction>();

        for (auto [entity, pos, speed, dir] : view.each())
        {
            registry.replace<components::position>(entity, pos.x + dir.x * speed.value * deltaTime, pos.y + dir.y * speed.value * deltaTime);
        }
    }
}
