#include "applyEffects.hpp"
#include "../components/type.hpp"
#include "../loader/effectLoader.hpp"
#include "components/health.hpp"
#include "components/target.hpp"

namespace features::effect::systems
{
	void applyEffects(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::effect::components::type, common::components::target>();
		for (auto [effect, type, target] : view.each())
		{
			if (registry.valid(target.entity))
			{
				switch (type.value)
				{
				case (features::effect::Type::Bleed): {
					float targetHealth = registry.get<common::components::health>(target.entity).value;
					targetHealth -= 5 * deltaTime;
					registry.emplace<common::components::health>(target.entity, targetHealth);
					break;
				}
				default:
					spdlog::warn("Effect with id {} not found", type.value);
					break;
				}
			}
		}
	}
}  // namespace features::effect::systems