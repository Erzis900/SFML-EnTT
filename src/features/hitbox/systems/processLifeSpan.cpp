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
			registry.replace<features::hitbox::components::hitbox>(entity, hitbox.initialLifeSpan, hitbox.lifeSpan - deltaTime, hitbox.hitCount,
																   hitbox.entities, hitbox.doneEntities);
			if (hitbox.lifeSpan <= 0.f)
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace features::hitbox::systems
