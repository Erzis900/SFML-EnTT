#include "removeAnimation.hpp"
#include "components/remove.hpp"
#include "features/animation/components/timer.hpp"

namespace features::animation::systems
{
	void removeAnimation(entt::registry &registry, features::animation::AnimationLoader &animationLoader)
	{
		auto view = registry.view<features::animation::components::timer>();
		for (auto [entity, timer] : view.each())
		{
			if (timer.value >= animationLoader.getTotalTime())
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::animation::systems