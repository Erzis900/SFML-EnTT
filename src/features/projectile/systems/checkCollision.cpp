#include "../entities/projectile.hpp"
#include "checkCollision.hpp"
#include "../components/isProjectile.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

namespace features::projectile::systems
{
    void checkCollision(entt::registry &registry)
    {
        auto projectileView = registry.view<features::projectile::components::isProjectile>();
        auto enemyView = registry.view<features::enemy::components::aiControlled, common::components::position>();  

        for (auto [projectileEntity, isProjectile] : projectileView.each())
        {
            for (auto [enemyEntity, aiControlled, position] : enemyView.each())
            {
                auto enemyPos = enemyView.get<common::components::position>(enemyEntity);
                std::cout << enemyPos.x << " " << enemyPos.y << std::endl;
            }
        }
    }
}