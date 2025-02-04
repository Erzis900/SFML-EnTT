#include "player.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, Config config, features::item::ItemsLoader &itemsLoader)
	{
		auto entity = registry.create();

		sf::CircleShape playerShape(config.player.radius);
		playerShape.setFillColor(sf::Color::Yellow);
		playerShape.setOrigin({playerShape.getRadius(), playerShape.getRadius()});

		createUnit(registry, itemsLoader, entity, {config.player.startX, config.player.startY});

		registry.emplace<features::player::components::playerControlled>(entity, true);
		registry.emplace<common::components::renderable>(entity, playerShape);
		registry.emplace<common::components::collider>(entity, config.player.radius);
		registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

		return entity;
	}
}  // namespace features::player::entities