#include "updateFrame.hpp"
#include "features/animation/components/elapsedTime.hpp"
#include "features/animation/components/frame.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::animation::components::frame, features::animation::components::elapsedTime>();
		for (auto [entity, frame, elapsedTime] : view.each())
		{
			elapsedTime.value += deltaTime;

			if (elapsedTime.value >= 0.05f)
			{
				elapsedTime.value = 0.f;
				frame.value++;
			}
		}
	}
}  // namespace features::animation::systems