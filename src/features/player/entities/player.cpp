#include "player.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, features::item::ItemsLoader &itemsLoader, features::unit::UnitsLoader &unitsLoader)
	{
		// auto entity = unitsLoader.createUnit(registry, 0, 200.f, 200.f);
		auto entity = unitsLoader.createUnit(registry, itemsLoader, 0, 700.f, 500.f);  // replace with above once saving progress is done

		registry.emplace<features::player::components::playerControlled>(entity, true);
		registry.emplace<features::player::components::camera>(entity, sf::View{});

		registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

		auto unit = registry.get<common::components::unit>(entity);
		auto unitBase = unitsLoader.getUnit(unit.id);
		auto mainhandEntity =
			features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Mainhand, 0.02f, 0.01f, 0.01f, 0.5f);
		auto offhandEntity = features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Offhand, 0.2f, 0.1f, 0.1f, 3.f);
		auto capeEntity = features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Cape, 0.02f, 0.01f, 0.01f, 0.5f);

		features::item::entities::equipItem(registry, itemsLoader, mainhandEntity, unitBase.mainhand, features::item::components::SlotType::Mainhand, false);
		features::item::entities::equipItem(registry, itemsLoader, offhandEntity, unitBase.offhand, features::item::components::SlotType::Offhand, false);
		features::item::entities::equipItem(registry, itemsLoader, capeEntity, unitBase.cape, features::item::components::SlotType::Cape, false);

		return entity;
	}
}  // namespace features::player::entities