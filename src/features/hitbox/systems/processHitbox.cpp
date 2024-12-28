#include "processHitbox.hpp"
#include "../entities/hitbox.hpp"
#include "../components/hitbox.hpp"
#include "components/area.hpp"
#include "components/collider.hpp"
#include "components/position.hpp"
#include "components/unit.hpp"
#include "components/faction.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_set>

namespace features::hitbox::systems
{
    void processHitbox(entt::registry &registry)
    {
        auto hitboxView = registry.view<features::hitbox::components::hitbox, common::components::faction, common::components::position, common::components::area>();
        auto unitView = registry.view<common::components::unit, common::components::faction, common::components::position, common::components::collider>();

        std::unordered_set<entt::entity> hitboxesToDestroy;
        std::unordered_set<entt::entity> unitsToDestroy;

        for (auto [hitboxEntity, hitbox, hitboxFaction, hitboxPos, area] : hitboxView.each())
        {
            for (auto [unitEntity, unit, unitFaction, enemyPos, coll] : unitView.each())
            {
                float deltaX = hitboxPos.x - enemyPos.x;
                float deltaY = hitboxPos.y - enemyPos.y;
                float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

                if (distance < (area.radius + coll.radius) && hitboxFaction.hasOverlap(hitboxFaction.foes, unitFaction.affiliation))
                {
                    hitboxesToDestroy.insert(hitboxEntity);
                    unitsToDestroy.insert(unitEntity);
                }
                // std::cout << enemyPos.x << " " << enemyPos.y << std::endl;
            }
        }

        for (auto hitboxEntity : hitboxesToDestroy)
        {
            registry.destroy(hitboxEntity);
        }

        for (auto unitEntity : unitsToDestroy)
        {
            registry.destroy(unitEntity);
        }
    }
}