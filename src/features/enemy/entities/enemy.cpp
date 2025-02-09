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

		createUnit(registry, entity, {pos.x, pos.y});

		registry.emplace<features::enemy::components::aiControlled>(entity, true);
		registry.emplace<common::components::renderable>(entity);
		registry.emplace<common::components::shape>(entity, enemyShape);
		registry.emplace<common::components::collider>(entity, config.enemy.radius);
		registry.emplace<common::components::faction>(entity, common::components::FOES_MASK, common::components::FOES_MASK, common::components::ALLY_MASK);

		features::item::entities::equipItem(registry, itemsLoader, entity, 0, features::item::components::SlotType::Mainhand, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 5, features::item::components::SlotType::Offhand, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 6, features::item::components::SlotType::Cape, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 4, features::item::components::SlotType::Head, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::MainShoulder, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::OffShoulder, true);

		features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Mainhand, 0.2f, 0.1f, 0.1f, 0.1f);

		// features::item::entities::unequipItem(registry, itemsLoader, mainhand);
		return entity;
	}
}  // namespace features::enemy::entities