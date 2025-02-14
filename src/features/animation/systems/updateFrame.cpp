#include "updateFrame.hpp"
#include "features/animation/components/timer.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::animation::components::timer>();
		for (auto [entity, timer] : view.each())
		{
			timer.value += deltaTime;
		}
	}
}  // namespace features::animation::systems