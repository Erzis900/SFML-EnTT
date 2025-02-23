#include "processEffects.hpp"
#include "../components/effect.hpp"
#include "components/health.hpp"
#include "components/remove.hpp"
#include "components/target.hpp"

namespace features::effect::systems
{
	void processEffects(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::effect::components::effect, common::components::target>();
		for (auto [entity, effect, target] : view.each())
		{
			float targetHealth = registry.get<common::components::health>(target.entity).value;
			// std::cout << targetHealth << std::endl;
			if (targetHealth <= 0.f)
			{
				spdlog::info("Effect {} has expired", effect.id);
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::effect::systems