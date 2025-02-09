#include "unit.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos)
{
	registry.emplace<common::components::unit>(entity, true);
	registry.emplace<common::components::position>(entity, pos.x, pos.y);
	registry.emplace<common::components::direction>(entity, 0.f, 0.f);
	registry.emplace<common::components::lookDirection>(entity, 0.f, 0.f);

	common::entities::initAttributes(registry, entity);
}
