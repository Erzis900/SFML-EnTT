#include "systems/moveEntities.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "components/direction.hpp"

namespace systems
{
    void moveEntities(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<components::position, components::speed, components::direction>();

        for (auto entity : view)
        {
            auto &pos = view.get<components::position>(entity);
            const auto &speed = view.get<components::speed>(entity);
            const auto &dir = view.get<components::direction>(entity);

            pos.x += static_cast<int>(dir.x * speed.value * deltaTime);
            pos.y += static_cast<int>(dir.y * speed.value * deltaTime);
        }
    }
}
