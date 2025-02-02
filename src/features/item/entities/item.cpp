#include "item.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, entt::entity unit, int itemId, features::item::components::SlotType slot)
	{
		auto entity = registry.create();
		registry.emplace<features::item::components::equipped>(entity, unit, slot);
		registry.emplace<features::item::components::itemId>(entity, itemId);
		return entity;
	}
}  // namespace features::item::entities
