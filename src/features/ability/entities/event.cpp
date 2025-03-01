#include "event.hpp"

namespace features::ability::entities
{
	entt::entity createEvent(entt::registry &registry, item::components::SlotType slotType, components::castEvent::State state, sf::Vector2f pointsAt,
							 entt::entity entityUnit)
	{
		auto entityEvent = registry.create();
		registry.emplace<components::castEvent>(entityEvent, entityUnit, state);
		registry.emplace<components::slot>(entityEvent, slotType);
		registry.emplace<common::components::lifespan>(entityEvent, 0.f);  // one tick alive
		registry.emplace<common::components::pointsAt>(entityEvent, pointsAt);

		return entityEvent;
	}
	entt::entity createEvent(entt::registry &registry, item::Trigger trigger, components::castEvent::State state, sf::Vector2f pointsAt,
							 entt::entity entityUnit)
	{
		auto entityEvent = registry.create();
		registry.emplace<components::castEvent>(entityEvent, entityUnit, state);
		registry.emplace<components::trigger>(entityEvent, trigger);
		registry.emplace<common::components::pointsAt>(entityEvent, pointsAt);
		return entityEvent;
	}
}  // namespace features::ability::entities