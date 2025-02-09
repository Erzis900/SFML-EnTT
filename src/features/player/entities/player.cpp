#include "player.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, Config config, features::item::ItemsLoader &itemsLoader)
	{
		auto entity = registry.create();

		sf::CircleShape playerShape(config.player.radius);
		playerShape.setFillColor(sf::Color::Yellow);
		playerShape.setOrigin({playerShape.getRadius(), playerShape.getRadius()});

		createUnit(registry, entity, {config.player.startX, config.player.startY});

		registry.emplace<features::player::components::playerControlled>(entity, true);
		registry.emplace<common::components::renderable>(entity);
		registry.emplace<common::components::shape>(entity, playerShape);
		registry.emplace<common::components::collider>(entity, config.player.radius);
		registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

		auto mainhandEntity =
			features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Mainhand, 0.2f, 0.1f, 0.1f, 0.1f);
		auto offhandEntity =
			features::ability::entities::createAbility(registry, entity, features::item::components::SlotType::Offhand, 0.2f, 0.1f, 0.1f, 0.1f);

		features::item::entities::equipItem(registry, itemsLoader, entity, 2, features::item::components::SlotType::Mainhand, true);
		features::item::entities::equipItem(registry, itemsLoader, mainhandEntity, 2, features::item::components::SlotType::Mainhand, false);

		features::item::entities::equipItem(registry, itemsLoader, entity, 5, features::item::components::SlotType::Offhand, true);
		features::item::entities::equipItem(registry, itemsLoader, offhandEntity, 5, features::item::components::SlotType::Offhand, false);

		features::item::entities::equipItem(registry, itemsLoader, entity, 6, features::item::components::SlotType::Cape, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 4, features::item::components::SlotType::Head, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::MainShoulder, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::OffShoulder, true);

		return entity;
	}
}  // namespace features::player::entities