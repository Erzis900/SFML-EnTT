#include "processHitbox.hpp"
#include "../entities/hitbox.hpp"
#include "../components/hitbox.hpp"
#include "components/area.hpp"
#include "components/remove.hpp"
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

        for (auto [hitboxEntity, hitbox, hitboxFaction, hitboxPos, area] : hitboxView.each())
        {
            for (auto [unitEntity, unit, unitFaction, enemyPos, coll] : unitView.each())
            {
                float deltaX = hitboxPos.x - enemyPos.x;
                float deltaY = hitboxPos.y - enemyPos.y;
                float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

                if (distance < (area.radius + coll.radius) && (unitFaction.affiliation & hitboxFaction.foes).any())
                {
                    registry.emplace_or_replace<common::components::remove>(hitboxEntity);
                    registry.emplace_or_replace<common::components::remove>(unitEntity);
                }
            }
        }
    }
}