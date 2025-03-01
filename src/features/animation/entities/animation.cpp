#include "animation.hpp"
#include "../components/color.hpp"
#include "area.hpp"
#include "components/attach.hpp"
#include "components/lifespan.hpp"
#include "components/position.hpp"

namespace features::animation::entities
{
	entt::entity createAnimation(entt::registry &registry, entt::entity &source, float radius, float totalTime)
	{
		auto entity = registry.create();
		registry.emplace<common::components::lifespan>(entity, totalTime, totalTime);
		registry.emplace<animation::components::Color>(entity, animation::components::Color::Blue);

		registry.emplace<common::components::position>(entity, 0.f, 0.f);
		registry.emplace<common::components::area>(entity, radius);
		registry.emplace<common::components::attach>(entity, source);

		return entity;
	}
}  // namespace features::animation::entities