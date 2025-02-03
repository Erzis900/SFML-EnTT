#include "unit.hpp"

void createUnit(entt::registry &registry, features::item::ItemsLoader &itemsLoader, entt::entity entity, sf::Vector2f pos)
{
	registry.emplace<common::components::unit>(entity, true);
	registry.emplace<common::components::position>(entity, pos.x, pos.y);
	registry.emplace<common::components::direction>(entity, 0.f, 0.f);
	registry.emplace<common::components::lookDirection>(entity, 0.f, 0.f);
	auto &attributes = registry.emplace<common::entities::Attributes>(entity, common::entities::Attributes{}).entities;
	attributes[common::entities::Stat::Health] = common::entities::createAttribute(registry, entity, common::entities::Stat::Health, 50.f);
	attributes[common::entities::Stat::MaxHealth] = common::entities::createAttribute(registry, entity, common::entities::Stat::MaxHealth, 50.f);
	attributes[common::entities::Stat::Speed] = common::entities::createAttribute(registry, entity, common::entities::Stat::Speed, 240.f);
	attributes[common::entities::Stat::Damage] = common::entities::createAttribute(registry, entity, common::entities::Stat::Damage, 10.f);
	attributes[common::entities::Stat::MinDamage] = common::entities::createAttribute(registry, entity, common::entities::Stat::MinDamage, 0.f);
	attributes[common::entities::Stat::MaxDamage] = common::entities::createAttribute(registry, entity, common::entities::Stat::MaxDamage, 5.f);

	features::item::entities::equipItem(registry, itemsLoader, entity, 0, features::item::components::SlotType::Mainhand);
	features::item::entities::equipItem(registry, itemsLoader, entity, 5, features::item::components::SlotType::Offhand);
	features::item::entities::equipItem(registry, itemsLoader, entity, 6, features::item::components::SlotType::Cape);
	features::item::entities::equipItem(registry, itemsLoader, entity, 4, features::item::components::SlotType::Head);
	features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::MainShoulder);
	features::item::entities::equipItem(registry, itemsLoader, entity, 3, features::item::components::SlotType::OffShoulder);

	features::ability::entities::createAbility(registry, entity, 0.2f, 0.1f, 0.1f, 0.1f);

	// features::item::entities::unequipItem(registry, itemsLoader, mainhand);
}