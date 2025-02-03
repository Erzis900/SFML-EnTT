#include "enemy.hpp"

float randomFloat(float min, float max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_real_distribution<> dis(min, max);
	return dis(gen);
}

namespace features::enemy::entities
{
	entt::entity createEnemy(entt::registry &registry, Config config, features::item::ItemsLoader &itemsLoader)
	{
		auto entity = registry.create();

		float minX = 100.f, maxX = 1000.f;
		float minY = 100.f, maxY = 600.f;

		sf::Vector2f pos = {randomFloat(minX, maxX), randomFloat(minY, maxY)};

		sf::CircleShape enemyShape(config.enemy.radius);
		enemyShape.setFillColor(sf::Color::Red);
		enemyShape.setOrigin({enemyShape.getRadius(), enemyShape.getRadius()});

		createUnit(registry, itemsLoader, entity, {pos.x, pos.y});

		registry.emplace<features::enemy::components::aiControlled>(entity, true);
		registry.emplace<common::components::renderable>(entity, enemyShape);
		registry.emplace<common::components::collider>(entity, config.enemy.radius);
		registry.emplace<common::components::faction>(entity, common::components::FOES_MASK, common::components::FOES_MASK, common::components::ALLY_MASK);

		registry.emplace<common::components::healthRegen>(entity, config.enemy.healthRegen);

		return entity;
	}
}  // namespace features::enemy::entities