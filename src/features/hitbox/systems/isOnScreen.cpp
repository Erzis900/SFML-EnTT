#include "isOnScreen.hpp"
#include "features/hitbox/components/hitbox.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"

namespace features::hitbox::systems
{
    void isOnScreen(entt::registry &registry, unsigned int screenWidth, unsigned int screenHeight)
    {
        auto hitboxView = registry.view<features::hitbox::components::hitbox, common::components::position>();

        for (auto [hitboxEntity, hitbox, position] : hitboxView.each())
        {
            auto pos = registry.get<common::components::position>(hitboxEntity);

            if (pos.x > screenWidth || pos.x < 0 || pos.y < 0 || pos.y > screenHeight)
            {
                registry.emplace<common::components::remove>(hitboxEntity);
            }
        }
    }
}