#include "player.hpp"
#include "entities/unit.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::player::entities
{
    entt::entity createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        createUnit(registry, entity);
        registry.emplace<features::player::components::playerControlled>(entity, true);
        return entity;
    }
}