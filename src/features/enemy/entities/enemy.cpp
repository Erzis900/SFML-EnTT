#include "enemy.hpp"
#include "utils.hpp"

namespace features::enemy::entities
{
	entt::entity createEnemy(entt::registry &registry, item::ItemsLoader &itemsLoader, unit::UnitsLoader &unitsLoader)
	{
		float minX = 1000.f, maxX = 1300.f;
		float minY = 700.f, maxY = 1200.f;
		sf::Vector2f pos = {utils::randomFloat(minX, maxX), utils::randomFloat(minY, maxY)};

		auto entity = unitsLoader.createUnit(registry, itemsLoader, 1, pos.x, pos.y);

		auto unit = registry.get<common::components::unit>(entity);
		auto unitBase = unitsLoader.getUnit(unit.id);

		registry.emplace<components::aiControlled>(entity);
		registry.emplace<common::components::faction>(entity, common::components::FOES_MASK, common::components::FOES_MASK, common::components::ALLY_MASK);

		auto mainhandEntity = ability::entities::createAbility(registry, entity, item::components::SlotType::Mainhand, 0.5f, 0.1f, 0.1f, 0.1f);
		item::entities::equipItem(registry, itemsLoader, mainhandEntity, unitBase.mainhand, item::components::SlotType::Mainhand, false);

		return entity;
	}
}  // namespace features::enemy::entities