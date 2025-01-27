#include "processInteraction.hpp"

#include "../components/hitbox.hpp"

#include "entities/attribute.hpp"
#include "components/attribute.hpp"
#include "components/source.hpp"
#include "components/health.hpp"

namespace features::hitbox::systems
{
    void processInteraction(entt::registry &registry)
    {
        auto hitboxView = registry.view<features::hitbox::components::hitbox, common::components::source>();
        for (auto [hitboxEntity, hitbox, source] : hitboxView.each())
        {
            for (auto entity : hitbox.entities)
            {
                auto &children = registry.get<common::entities::Attributes>(source.entity);
                auto &damage = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Damage]);
                auto health = registry.get<common::components::health>(entity);
                registry.replace<common::components::health>(entity, health.value - damage.value);
            }
            auto it = std::next(hitbox.entities.begin(), hitbox.entities.size());

            std::move(hitbox.entities.begin(), it, std::back_inserter(hitbox.doneEntities));

            hitbox.entities.erase(hitbox.entities.begin(), it);
            registry.replace<features::hitbox::components::hitbox>(hitboxEntity, hitbox.lifeSpan, hitbox.initialLifeSpan, hitbox.hitCount, hitbox.entities, hitbox.doneEntities);
        }
    }
}
