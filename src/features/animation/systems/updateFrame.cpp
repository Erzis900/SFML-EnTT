#include "updateFrame.hpp"
#include "components/attach.hpp"
#include "components/remove.hpp"
#include "features/animation/components/timer.hpp"
#include "features/hitbox/components/hitbox.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime, features::animation::AnimationLoader &animationLoader)
	{
		auto view = registry.view<features::animation::components::timer>();
		for (auto [entity, timer] : view.each())
		{
			timer.value += deltaTime;

			auto hitboxView = registry.view<features::hitbox::components::hitbox>();
			for (auto [hitboxEntity, hitbox] : hitboxView.each())
			{
				if (timer.value > animationLoader.getTotalTime() || hitbox.lifeSpan <= 0.f || hitbox.hitCount <= 0.f)
				{
					registry.remove<common::components::attach>(entity);
					if (registry.valid(entity))
					{
						registry.emplace_or_replace<common::components::remove>(entity);
					}
				}
			}
		}
	}
}  // namespace features::animation::systems