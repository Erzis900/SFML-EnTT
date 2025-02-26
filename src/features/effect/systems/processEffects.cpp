#include "processEffects.hpp"

namespace features::effect::systems
{
	void processEffects(entt::registry &registry, float deltaTime, EffectsLoader &effectsLoader)
	{
		auto view = registry.view<features::effect::components::affected>();
		for (auto [entity, affected] : view.each())
		{
			auto nextTime = affected.remainingTime - deltaTime;
			registry.replace<features::effect::components::affected>(entity, affected.target, nextTime);
			if (nextTime <= 0.f)
			{
				spdlog::info("Affected entity {} has expired", static_cast<int>(entity));
				entities::removeEffect(registry, effectsLoader, entity);
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::effect::systems