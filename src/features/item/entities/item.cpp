#include "item.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, ItemsLoader &itemLoader, entt::entity unit, int itemId, components::SlotType slot, bool renderable)
	{
		auto entity = registry.create();
		registry.emplace<components::equipped>(entity, unit, slot);
		registry.emplace<components::itemId>(entity, itemId);
		if (renderable)
		{
			registry.emplace<common::components::renderable>(entity);
		}

		auto attributes = registry.get<common::entities::Attributes>(unit);
		auto item = itemLoader.getItem(itemId);
		common::entities::applyModifiers(registry, entity, attributes, item.modifiers);

		return entity;
	}

	bool unequipItem(entt::registry &registry, ItemsLoader &itemLoader, entt::entity equippedEntity)
	{
		auto equipped = registry.get<components::equipped>(equippedEntity);
		auto itemId = registry.get<components::itemId>(equippedEntity).id;
		auto unit = equipped.unit;
		auto &attributes = registry.get<common::entities::Attributes>(unit);
		auto item = itemLoader.getItem(itemId);
		common::entities::removeModifiers(registry, equippedEntity, attributes, item.modifiers);

		registry.destroy(equippedEntity);
		return true;
	}
}  // namespace features::item::entities
