#include "inc/entt.hpp"
#include "components/position.hpp"
#include "components/velocity.hpp"

namespace entities
{
    entt::entity createProjectile(entt::registry &registry)
    {
        const auto entity = registry.create();
        registry.emplace<components::position>(entity, i * 30.f, i * 150.f);
        registry.emplace<components::velocity>(entity, 2.f, 2.f);
        return entity;
    }

}
