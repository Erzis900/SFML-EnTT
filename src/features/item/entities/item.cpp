#include "item.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity unit, int itemId,
						   features::item::components::SlotType slot, bool renderable)
	{
		auto entity = registry.create();
		registry.emplace<features::item::components::equipped>(entity, unit, slot);
		registry.emplace<features::item::components::itemId>(entity, itemId);
		if (renderable)
		{
			registry.emplace<common::components::renderable>(entity);
		}

		auto attributes = registry.get<common::entities::Attributes>(unit);
		auto item = itemLoader.getItem(itemId);
		common::entities::applyModifiers(registry, entity, attributes, item.modifiers);

		return entity;
	}

	bool unequipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity equippedEntity)
	{
		auto equipped = registry.get<features::item::components::equipped>(equippedEntity);
		auto itemId = registry.get<features::item::components::itemId>(equippedEntity).id;
		auto unit = equipped.unit;
		auto &attributes = registry.get<common::entities::Attributes>(unit);
		auto item = itemLoader.getItem(itemId);
		common::entities::removeModifiers(registry, equippedEntity, attributes, item.modifiers);

		registry.destroy(equippedEntity);
		return true;
	}
}  // namespace features::item::entities
