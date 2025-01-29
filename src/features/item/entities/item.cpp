#include "item.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, entt::entity unit, int itemId, features::item::components::SlotType slot, int coord)
	{
		auto entity = registry.create();
		registry.emplace<features::item::components::equipped>(entity, unit, itemId, slot, coord);
		return entity;
	}
}  // namespace features::item::entities
