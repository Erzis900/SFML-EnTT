#include "effect.hpp"
#include "components/lifespan.hpp"
#include "components/target.hpp"
#include "features/effect/components/effect.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, features::effect::EffectLoader &effectLoader, features::effect::Effects id, entt::entity target)
	{
		auto entity = registry.create();
		registry.emplace<common::components::target>(entity, target);
		registry.emplace<features::effect::components::effect>(entity, id, effectLoader.getEffect(id).duration, effectLoader.getEffect(id).stacks,
															   effectLoader.getEffect(id).refresh);

		registry.emplace<common::components::lifespan>(entity, effectLoader.getEffect(id).duration, effectLoader.getEffect(id).duration);
		return entity;
	}
}  // namespace features::effect::entities