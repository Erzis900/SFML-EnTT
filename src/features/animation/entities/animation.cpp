#include "animation.hpp"
#include "../components/color.hpp"
#include "../components/timer.hpp"
#include "area.hpp"
#include "components/attach.hpp"
#include "components/position.hpp"

namespace features::animation::entities
{
	entt::entity createAnimation(entt::registry &registry, entt::entity &source, float radius)
	{
		auto entity = registry.create();
		registry.emplace<features::animation::components::timer>(entity, 0.f);
		registry.emplace<features::animation::components::Color>(entity, features::animation::components::Color::Blue);

		registry.emplace<common::components::position>(entity, 0.f, 0.f);
		registry.emplace<common::components::area>(entity, radius);
		registry.emplace<common::components::attach>(entity, source);

		return entity;
	}
}  // namespace features::animation::entities