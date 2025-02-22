#include "processLifespan.hpp"
#include "components/lifespan.hpp"
#include "components/remove.hpp"

namespace common::systems
{
	void processLifespan(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<common::components::lifespan>();

		for (auto [entity, lifespan] : view.each())
		{
			registry.replace<common::components::lifespan>(entity, lifespan.time - deltaTime, lifespan.totalTime);

			if (lifespan.time - deltaTime <= 0.f)
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace common::systems