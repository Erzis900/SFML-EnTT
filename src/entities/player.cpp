#include "player.hpp"
#include "unit.hpp"
#include "components/playerControlled.hpp"

namespace entities
{
    entt::entity createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        createUnit(registry, entity);
        registry.emplace<components::playerControlled>(entity, true);
        return entity;
    }
}