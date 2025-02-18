#include "processLifespan.hpp"
#include "../components/hitbox.hpp"
#include "components/remove.hpp"

namespace features::hitbox::systems
{
	void processLifeSpan(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<features::hitbox::components::hitbox>();

		for (auto [entity, hitbox] : view.each())
		{
			registry.replace<features::hitbox::components::hitbox>(entity, hitbox.lifeSpan - deltaTime, hitbox.initialLifeSpan, hitbox.hitCount,
																   hitbox.entities, hitbox.doneEntities);

			if (hitbox.lifeSpan - deltaTime <= 0.f)
			{
				spdlog::debug("Hitbox {} lifeSpan removed", static_cast<int>(entity));
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::hitbox::systems
