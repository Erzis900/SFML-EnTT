#include "updateFrame.hpp"
#include "components/remove.hpp"
#include "features/animation/components/timer.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime, features::animation::AnimationLoader &animationLoader)
	{
		auto view = registry.view<features::animation::components::timer>();
		for (auto [entity, timer] : view.each())
		{
			timer.value += deltaTime;

			if (timer.value > animationLoader.getTotalTime())
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::animation::systems