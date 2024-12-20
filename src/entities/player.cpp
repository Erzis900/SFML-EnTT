#include "player.hpp"
#include "unit.hpp" 

namespace entities 
{
    entt::entity createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();
        createUnit(registry, entity);
        return entity;
    }
}