#include "isOnScreen.hpp"
#include "features/projectile/components/isProjectile.hpp"
#include "components/position.hpp"

namespace features::projectile::systems
{
    void isOnScreen(entt::registry &registry)
    {
        auto projectileView = registry.view<features::projectile::components::isProjectile, common::components::position>();

        for (auto [projectileEntity, isProjectile, position] : projectileView.each())
        {
            auto pos = registry.get<common::components::position>(projectileEntity);
            
            // TODO not hard coding these values
            if (pos.x > 1280 || pos.x < 0 || pos.y < 0 || pos.y > 720)
            {
                registry.destroy(projectileEntity);
            }
        }
    }
}