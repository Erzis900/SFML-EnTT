#include "animation.hpp"
#include "../components/timer.hpp"
#include "components/position.hpp"
#include "components/source.hpp"

namespace features::animation::entities
{
	entt::entity createAnimation(entt::registry &registry, entt::entity &source)
	{
		auto entity = registry.create();
		registry.emplace<features::animation::components::timer>(entity, 0.f);

		registry.emplace<common::components::position>(entity, 0.f, 0.f);
		registry.emplace<common::components::source>(entity, source);

		return entity;
	}
}  // namespace features::animation::entities