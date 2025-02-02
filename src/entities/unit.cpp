#include "unit.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos, float speed, float health, float maxHealth)
{
	registry.emplace<common::components::unit>(entity, true);
	registry.emplace<common::components::position>(entity, pos.x, pos.y);
	registry.emplace<common::components::direction>(entity, 0.f, 0.f);
	registry.emplace<common::components::lookDirection>(entity, 0.f, 0.f);
	registry.emplace<common::components::speed>(entity, speed);
	registry.emplace<common::components::health>(entity, health);
	registry.emplace<common::components::maxHealth>(entity, maxHealth);
	auto &attributes = registry.emplace<common::entities::Attributes>(entity, common::entities::Attributes{}).entities;
	attributes[common::entities::Stat::Health] = common::entities::createAttribute(registry, common::entities::Stat::Health, health);
	attributes[common::entities::Stat::MaxHealth] = common::entities::createAttribute(registry, common::entities::Stat::MaxHealth, maxHealth);
	attributes[common::entities::Stat::Speed] = common::entities::createAttribute(registry, common::entities::Stat::Speed, speed);
	attributes[common::entities::Stat::Damage] = common::entities::createAttribute(registry, common::entities::Stat::Damage, 10.f);
	auto modifier1 = common::entities::createModifier(registry, common::entities::Scope::Flat, 10.f);
	auto modifier2 = common::entities::addModifier(registry, modifier1, common::entities::Scope::Flat, 10.f);
	auto modifier3 = common::entities::addModifier(registry, modifier2, common::entities::Scope::Flat, 10.f);

	features::item::entities::equipItem(registry, entity, 0, features::item::components::SlotType::Mainhand);
	features::item::entities::equipItem(registry, entity, 5, features::item::components::SlotType::Offhand);
	features::item::entities::equipItem(registry, entity, 6, features::item::components::SlotType::Cape);
	features::item::entities::equipItem(registry, entity, 4, features::item::components::SlotType::Head);
	features::item::entities::equipItem(registry, entity, 3, features::item::components::SlotType::MainShoulder);
	features::item::entities::equipItem(registry, entity, 3, features::item::components::SlotType::OffShoulder);

	registry.get<common::components::relationship>(attributes[common::entities::Stat::Speed]).first_child = modifier1;
	registry.emplace<common::components::recalculate>(attributes[common::entities::Stat::Speed], true);
}