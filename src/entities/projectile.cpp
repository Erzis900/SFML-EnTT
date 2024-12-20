#include "inc/entt.hpp"
#include "components/position.hpp"
#include "components/velocity.hpp"

namespace entities
{
    entt::entity createProjectile(entt::registry &registry)
    {
        auto entity = registry.create();
        registry.emplace<components::position>(entity, 30.f, 150.f);
        registry.emplace<components::velocity>(entity, 2.f, 2.f);
        return entity;
    }

}
