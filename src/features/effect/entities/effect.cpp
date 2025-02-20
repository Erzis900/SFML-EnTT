#include "effect.hpp"
#include "components/target.hpp"
#include "features/effect/components/duration.hpp"
#include "features/effect/components/refresh.hpp"
#include "features/effect/components/stacks.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, entt::entity &target, const std::string &effectName, features::effect::EffectLoader &effectLoader)
	{
		auto entity = registry.create();
		registry.emplace<common::components::target>(entity, target);
		registry.emplace<features::effect::components::duration>(entity, effectLoader.getEffect(effectName).duration);
		registry.emplace<features::effect::components::stacks>(entity, effectLoader.getEffect(effectName).stacks);
		registry.emplace<features::effect::components::refresh>(entity, effectLoader.getEffect(effectName).refresh);

		return entity;
	}
}  // namespace features::effect::entities