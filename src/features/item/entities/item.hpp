#pragma once
#include "pch.hpp"

#include "components/modifiers.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/renderable.hpp"
#include "entities/attribute.hpp"

#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "../loader/itemsLoader.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, ItemsLoader &itemLoader, entt::entity unit, int itemId, components::SlotType slot, bool renderable);
	bool unequipItem(entt::registry &registry, ItemsLoader &itemLoader, entt::entity equippedEntity);
}  // namespace features::item::entities