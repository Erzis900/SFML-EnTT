#include "unit.hpp"
#include "components/position.hpp"
#include "components/velocity.hpp"

void createUnit(entt::registry &registry, entt::entity entity)
{
    registry.emplace<components::position>(entity, 200.f, 200.f);
    registry.emplace<components::velocity>(entity, 2.f, 2.f);
}