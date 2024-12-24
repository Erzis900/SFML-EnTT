#include "../entities/projectile.hpp"
#include "checkCollision.hpp"
#include "../components/isProjectile.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

namespace features::projectile::systems
{
    void checkCollision(entt::registry &registry)
    {
        auto projectileView = registry.view<features::projectile::components::isProjectile, common::components::position>();
        auto enemyView = registry.view<features::enemy::components::aiControlled, common::components::position>();  

        std::vector<entt::entity> projectilesToDestroy;
        std::vector<entt::entity> enemiesToDestroy;

        for (auto [projectileEntity, isProjectile, position] : projectileView.each())
        {
            for (auto [enemyEntity, aiControlled, position] : enemyView.each())
            {
                auto enemyPos = enemyView.get<common::components::position>(enemyEntity);
                auto projectilePos = projectileView.get<common::components::position>(projectileEntity);

                float deltaX = projectilePos.x - enemyPos.x;
                float deltaY = projectilePos.y - enemyPos.y;
                float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

                // TODO not hardcoding these values
                float projectileRadius = 10.f;
                float enemyRadius = 50.f;

                if (distance < (projectileRadius + enemyRadius))
                {
                    projectilesToDestroy.push_back(projectileEntity);
                    enemiesToDestroy.push_back(enemyEntity);
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