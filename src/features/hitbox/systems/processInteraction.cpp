#include "processInteraction.hpp"

namespace features::hitbox::systems
{
	void processInteraction(entt::registry &registry, effect::EffectsLoader &effectsLoader)
	{
		auto hitboxView = registry.view<hitbox::components::hitbox, common::components::source>();
		for (auto [hitboxEntity, hitbox, source] : hitboxView.each())
		{
			for (auto entity : hitbox.entities)
			{
				if (registry.valid(source.entity))
				{
					auto &children = registry.get<common::entities::Attributes>(source.entity);
					auto &damage = registry.get<common::components::attribute>(children.entities[common::entities::Stat::Damage]);
					auto &health = registry.get<common::components::health>(entity);
					effect::entities::applyEffect(registry, effectsLoader, effect::Effects::Bleed, entity);
					auto pointsAt = registry.get<common::components::pointsAt>(source.entity);
					ability::entities::createEvent(registry, item::Trigger::OnHit, ability::components::castEvent::State::Press, pointsAt.position,
												   source.entity);

					health.value -= damage.value;
				}
			}
			auto it = std::next(hitbox.entities.begin(), hitbox.entities.size());

			std::move(hitbox.entities.begin(), it, std::back_inserter(hitbox.doneEntities));

			hitbox.entities.erase(hitbox.entities.begin(), it);
			registry.replace<hitbox::components::hitbox>(hitboxEntity, hitbox.hitCount, hitbox.entities, hitbox.doneEntities);
		}
	}
}  // namespace features::hitbox::systems
