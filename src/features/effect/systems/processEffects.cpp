#include "processEffects.hpp"
#include "../components/duration.hpp"
#include "components/health.hpp"
#include "components/remove.hpp"
#include "components/target.hpp"

namespace features::effect::systems
{
	void processEffects(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::effect::components::duration, common::components::target>();
		for (auto [entity, duration, target] : view.each())
		{
			duration.value -= deltaTime;

			float targetHealth = registry.get<common::components::health>(target.entity).value;
			if (duration.value <= 0.f || targetHealth <= 0.f)
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::effect::systems