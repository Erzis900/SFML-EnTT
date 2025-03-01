#include "player.hpp"
#include "components/visible.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, item::ItemsLoader &itemsLoader, unit::UnitsLoader &unitsLoader)
	{
		// auto entity = unitsLoader.createUnit(registry, 0, 200.f, 200.f);
		auto entity = unitsLoader.createUnit(registry, itemsLoader, 0, 700.f, 500.f);  // replace with above once saving progress is done

		registry.emplace<components::playerControlled>(entity);
		registry.emplace<components::camera>(entity, sf::View{});
		registry.emplace<common::components::visible>(entity);

		registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

		auto unit = registry.get<common::components::unit>(entity);
		auto unitBase = unitsLoader.getUnit(unit.id);
		auto mainhandEntity = ability::entities::createAbility(registry, entity, item::components::SlotType::Mainhand, 0.02f, 0.01f, 0.01f, 0.5f);
		auto offhandEntity = ability::entities::createAbility(registry, entity, item::components::SlotType::Offhand, 0.5f, 0.1f, 0.1f, 3.f);
		auto capeEntity = ability::entities::createAbility(registry, entity, item::components::SlotType::Cape, 0.02f, 1.f, 0.01f, 0.5f);
		auto shoulderEntity = ability::entities::createAbility(registry, entity, item::components::SlotType::MainShoulder, 0.f, 1.f, 0.01f, 0.5f);

		item::entities::equipItem(registry, itemsLoader, mainhandEntity, unitBase.mainhand, item::components::SlotType::Mainhand, false);
		item::entities::equipItem(registry, itemsLoader, offhandEntity, unitBase.offhand, item::components::SlotType::Offhand, false);
		item::entities::equipItem(registry, itemsLoader, capeEntity, unitBase.cape, item::components::SlotType::Cape, false);
		item::entities::equipItem(registry, itemsLoader, shoulderEntity, unitBase.mainShoulder, item::components::SlotType::MainShoulder, false);

		return entity;
	}
}  // namespace features::player::entities