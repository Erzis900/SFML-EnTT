#include "regenerateHealth.hpp"
#include "components/health.hpp"
#include "components/healthRegen.hpp"
#include "components/maxHealth.hpp"

namespace common::systems
{
	void regenerateHealth(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<common::components::health, common::components::maxHealth, common::components::healthRegen>();

		for (auto [entity, health, maxHealth, healthRegen] : view.each())
		{
			if (health.value > 0.f)
			{
				registry.replace<common::components::health>(entity, std::min(health.value + healthRegen.value * deltaTime, maxHealth.value));
			}
		}
	}
}  // namespace common::systems
