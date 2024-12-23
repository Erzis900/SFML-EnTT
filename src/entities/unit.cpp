#include "unit.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "components/direction.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f &pos, float speed)
{
    registry.emplace<common::components::position>(entity, pos.x, pos.y);
    registry.emplace<common::components::direction>(entity, 0.f, 0.f);
    registry.emplace<common::components::speed>(entity, speed);
    registry.emplace<common::components::health>(entity, 100);
    registry.emplace<common::components::maxHealth>(entity, 100);
}