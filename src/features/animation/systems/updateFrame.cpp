#include "updateFrame.hpp"
#include "components/attach.hpp"
#include "components/remove.hpp"
#include "features/animation/components/timer.hpp"
#include "features/hitbox/components/hitbox.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::animation::components::timer>();

		for (auto [entity, timer] : view.each())
		{
			registry.replace<features::animation::components::timer>(entity, timer.value - deltaTime, timer.totalTime);

			if (timer.value - deltaTime <= 0.f)
			{
				spdlog::debug("Animation {} lifeSpan removed", static_cast<int>(entity));
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::animation::systems