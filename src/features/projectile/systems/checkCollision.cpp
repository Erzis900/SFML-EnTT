#include "../entities/projectile.hpp"
#include "checkCollision.hpp"
#include "../components/isProjectile.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_set>

namespace features::projectile::systems
{
    void checkCollision(entt::registry &registry, float projectileRadius, float enemyRadius)
    {
        auto projectileView = registry.view<features::projectile::components::isProjectile, common::components::position>();
        auto enemyView = registry.view<features::enemy::components::aiControlled, common::components::position>();

        std::unordered_set<entt::entity> projectilesToDestroy;
        std::unordered_set<entt::entity> enemiesToDestroy;

        for (auto [projectileEntity, isProjectile, projectilePos] : projectileView.each())
        {
            for (auto [enemyEntity, aiControlled, enemyPos] : enemyView.each())
            {
                float deltaX = projectilePos.x - enemyPos.x;
                float deltaY = projectilePos.y - enemyPos.y;
                float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

                if (distance < (projectileRadius + enemyRadius))
                {
                    projectilesToDestroy.insert(projectileEntity);
                    enemiesToDestroy.insert(enemyEntity);
                }
                // std::cout << enemyPos.x << " " << enemyPos.y << std::endl;
            }
        }

        for (auto projectile : projectilesToDestroy)
        {
            registry.destroy(projectile);
        }

        for (auto enemy : enemiesToDestroy)
        {
            registry.destroy(enemy);
        }
    }
}