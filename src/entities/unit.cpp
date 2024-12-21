#include "unit.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "components/direction.hpp"

void createUnit(entt::registry &registry, entt::entity entity)
{
    registry.emplace<components::position>(entity, 200.f, 200.f);
    registry.emplace<components::direction>(entity, 0.f, 0.f);
    registry.emplace<components::speed>(entity, 150.f);
}