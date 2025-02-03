#include "ability.hpp"

namespace features::ability::entities
{
	entt::entity createAbility(entt::registry &registry, entt::entity unit, float castTime, float activeTime, float delayTime, float cooldown)
	{
		auto entity = registry.create();
		registry.emplace<features::ability::components::ability>(entity, unit, castTime, activeTime, delayTime, cooldown);
		registry.emplace<features::ability::components::ready>(entity);
		registry.emplace<common::entities::Attributes>(entity, common::entities::Attributes{});
		return entity;
	}
}  // namespace features::ability::entities