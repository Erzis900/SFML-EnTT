#include "isOnScreen.hpp"
#include "features/projectile/components/isProjectile.hpp"
#include "components/position.hpp"

namespace features::projectile::systems
{
    void isOnScreen(entt::registry &registry, unsigned int screenWidth, unsigned int screenHeight)
    {
        auto projectileView = registry.view<features::projectile::components::isProjectile, common::components::position>();

        for (auto [projectileEntity, isProjectile, position] : projectileView.each())
        {
            auto pos = registry.get<common::components::position>(projectileEntity);
            
            if (pos.x > screenWidth || pos.x < 0 || pos.y < 0 || pos.y > screenHeight)
            {
                registry.destroy(projectileEntity);
            }
        }
    }
}