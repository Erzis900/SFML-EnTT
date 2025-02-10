#include "player.hpp"
#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/healthRegen.hpp"
#include "components/renderable.hpp"
#include "entities/unit.hpp"
#include "features/player/components/camera.hpp"
#include "features/player/components/cooldown.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, Config config, sf::RenderWindow &window)
	{
		auto entity = registry.create();

		sf::CircleShape playerShape(config.player.radius);
		playerShape.setFillColor(sf::Color::Yellow);
		playerShape.setOrigin({playerShape.getRadius(), playerShape.getRadius()});

		sf::Vector2f startPos = {static_cast<float>(window.getSize().x / 2), static_cast<float>(window.getSize().y / 2)};

		createUnit(registry, entity, startPos, {0, 0}, config.player.speed, config.player.health, config.player.maxHealth);

		registry.emplace<features::player::components::playerControlled>(entity, true);
		registry.emplace<features::player::components::cooldown>(entity, config.player.cooldown);
		registry.emplace<features::player::components::camera>(entity, sf::View{});

		registry.emplace<common::components::renderable>(entity, playerShape);
		registry.emplace<common::components::collider>(entity, config.player.radius);
		registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

		registry.emplace<common::components::healthRegen>(entity, config.player.healthRegen);

		return entity;
	}
}  // namespace features::player::entities