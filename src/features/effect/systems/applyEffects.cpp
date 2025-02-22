#include "applyEffects.hpp"
#include "../components/effect.hpp"
#include "../loader/effectLoader.hpp"
#include "components/health.hpp"
#include "components/target.hpp"

namespace features::effect::systems
{
	void applyEffects(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::effect::components::effect, common::components::target>();
		for (auto [entity, effect, target] : view.each())
		{
			if (registry.valid(target.entity))
			{
				switch (effect.id)
				{
				case (features::effect::Effects::Bleed): {
					float targetHealth = registry.get<common::components::health>(target.entity).value;
					targetHealth -= 5 * deltaTime;
					registry.replace<common::components::health>(target.entity, targetHealth);
					break;
				}
				default:
					spdlog::warn("Effect with id {} not found", effect.id);
					break;
				}
			}
		}
	}
}  // namespace features::effect::systems