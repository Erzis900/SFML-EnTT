#include "ability.hpp"

namespace features::ability::entities
{
	entt::entity createAbility(entt::registry &registry, entt::entity unit, features::item::components::SlotType slotType, float castTime, float activeTime,
							   float delayTime, float cooldown)
	{
		auto entity = registry.create();
		registry.emplace<features::ability::components::ability>(entity, unit, slotType, castTime, activeTime, delayTime, cooldown);
		registry.emplace<features::ability::components::ready>(entity);

		common::entities::initAttributes(registry, entity);

		return entity;
	}
}  // namespace features::ability::entities