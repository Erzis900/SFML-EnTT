#include "effect.hpp"
#include "components/target.hpp"
#include "features/effect/components/duration.hpp"
#include "features/effect/components/refresh.hpp"
#include "features/effect/components/stacks.hpp"
#include "features/effect/components/type.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, entt::entity target, features::effect::Type type, features::effect::EffectLoader &effectLoader)
	{
		auto entity = registry.create();
		registry.emplace<common::components::target>(entity, target);
		registry.emplace<features::effect::components::type>(entity, type);
		registry.emplace<features::effect::components::duration>(entity, effectLoader.getEffect(type).duration);
		registry.emplace<features::effect::components::stacks>(entity, effectLoader.getEffect(type).stacks);
		registry.emplace<features::effect::components::refresh>(entity, effectLoader.getEffect(type).refresh);

		return entity;
	}
}  // namespace features::effect::entities