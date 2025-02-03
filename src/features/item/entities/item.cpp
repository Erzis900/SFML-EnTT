#include "item.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity unit, int itemId,
						   features::item::components::SlotType slot)
	{
		auto entity = registry.create();
		registry.emplace<features::item::components::equipped>(entity, unit, slot);
		registry.emplace<features::item::components::itemId>(entity, itemId);

		auto &attributes = registry.get<common::entities::Attributes>(unit).entities;
		auto item = itemLoader.getItem(itemId);

		for (auto modifier : item.modifiers)
		{
			auto modifierEntity = common::entities::createModifier(registry, entity, modifier.scope, modifier.value);

			auto &relationship = registry.get<common::components::relationship>(attributes[modifier.attribute]);
			if (relationship.first_child == entt::null)
			{
				relationship.first_child = modifierEntity;
			}
			else
			{
				auto lastModifier = relationship.first_child;
				while (registry.get<common::components::relationship>(lastModifier).next != entt::null)
				{
					lastModifier = registry.get<common::components::relationship>(lastModifier).next;
				}
				registry.get<common::components::relationship>(lastModifier).next = modifierEntity;
				registry.get<common::components::relationship>(modifierEntity).prev = lastModifier;
			}
			registry.emplace_or_replace<common::components::recalculate>(attributes[modifier.attribute], true);
		}
		return entity;
	}
	bool unequipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity equippedEntity)
	{
		auto equipped = registry.get<features::item::components::equipped>(equippedEntity);
		auto itemId = registry.get<features::item::components::itemId>(equippedEntity).id;
		auto unit = equipped.unit;
		auto &attributes = registry.get<common::entities::Attributes>(unit).entities;
		auto item = itemLoader.getItem(itemId);

		for (auto modifier : item.modifiers)
		{
			auto &relationship = registry.get<common::components::relationship>(attributes[modifier.attribute]);
			auto modifierEntity = relationship.first_child;
			while (modifierEntity != entt::null)
			{
				if (registry.get<common::components::relationship>(modifierEntity).source == equippedEntity)
				{
					auto &mod = registry.get<common::components::modifier>(modifierEntity);
					auto &modifierRelationship = registry.get<common::components::relationship>(modifierEntity);
					if (modifierRelationship.prev != entt::null)
					{
						registry.get<common::components::relationship>(modifierRelationship.prev).next = modifierRelationship.next;
					}
					if (modifierRelationship.next != entt::null)
					{
						registry.get<common::components::relationship>(modifierRelationship.next).prev = modifierRelationship.prev;
					}
					if (relationship.first_child == modifierEntity)
					{
						relationship.first_child = modifierRelationship.next;
					}
					registry.destroy(modifierEntity);
					modifierEntity = modifierRelationship.next;
				}
			}
			registry.emplace_or_replace<common::components::recalculate>(attributes[modifier.attribute], true);
		}
		registry.destroy(equippedEntity);
		return true;
	}
}  // namespace features::item::entities
