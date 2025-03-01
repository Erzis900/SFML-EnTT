#pragma once

#include "pch.hpp"

#include "components/lifespan.hpp"
#include "components/pointsAt.hpp"

#include "features/item/loader/itemsLoader.hpp"

#include "../components/castEvent.hpp"
#include "../components/slot.hpp"
#include "../components/trigger.hpp"

namespace features::ability::entities
{
	entt::entity createEvent(entt::registry &registry, item::components::SlotType slotType, components::castEvent::State state, sf::Vector2f mousePos,
							 entt::entity entityUnit);

	entt::entity createEvent(entt::registry &registry, item::Trigger trigger, components::castEvent::State state, sf::Vector2f mousePos,
							 entt::entity entityUnit);
}  // namespace features::ability::entities