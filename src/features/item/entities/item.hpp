#pragma once
#include "pch.hpp"

#include "components/modifiers.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "entities/attribute.hpp"

#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "../loader/itemsLoader.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity unit, int itemId,
						   features::item::components::SlotType slot);
	bool unequipItem(entt::registry &registry, features::item::ItemsLoader &itemLoader, entt::entity equippedEntity);
}  // namespace features::item::entities