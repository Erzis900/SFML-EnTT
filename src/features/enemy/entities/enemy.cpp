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
	entt::entity createEnemy(entt::registry &registry, features::item::ItemsLoader &itemsLoader, features::unit::UnitsLoader &unitsLoader)
	{
		float minX = 1000.f, maxX = 1300.f;
		float minY = 700.f, maxY = 1200.f;
		sf::Vector2f pos = {randomFloat(minX, maxX), randomFloat(minY, maxY)};

		auto entity = unitsLoader.createUnit(registry, itemsLoader, 1, pos.x, pos.y);

		auto unit = registry.get<common::components::unit>(entity);
		auto unitBase = unitsLoader.getUnit(unit.id);

		registry.emplace<features::enemy::components::aiControlled>(entity, true);
		registry.emplace<common::components::faction>(entity, common::components::FOES_MASK, common::components::FOES_MASK, common::components::ALLY_MASK);

		auto mainhandEntity =
			features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Mainhand, 0.5f, 0.1f, 0.1f, 0.1f);
		features::item::entities::equipItem(registry, itemsLoader, mainhandEntity, unitBase.mainhand, features::item::components::SlotType::Mainhand, false);

		return entity;
	}
}  // namespace features::enemy::entities