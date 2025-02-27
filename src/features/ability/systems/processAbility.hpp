#pragma once
#include "pch.hpp"

#include "../components/ability.hpp"
#include "../components/active.hpp"
#include "../components/cast.hpp"
#include "../components/castEvent.hpp"
#include "../components/cooldown.hpp"
#include "../components/delay.hpp"
#include "../components/pointsAt.hpp"
#include "../components/ready.hpp"

#include "components/attribute.hpp"
#include "components/direction.hpp"
#include "entities/attribute.hpp"

#include "features/hitbox/entities/hitbox.hpp"
#include "features/player/components/initialCooldown.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::ability::systems
{
	void processAbility(entt::registry &registry, float deltaTime);

	void processReady(entt::registry &registry);
	void processCast(entt::registry &registry, float deltaTime);
	void processActive(entt::registry &registry, float deltaTime);
	void processDelay(entt::registry &registry, float deltaTime);
	void processCooldown(entt::registry &registry, float deltaTime);
	void processCastCancel(entt::registry &registry);
	void processRoll(entt::registry &registry, float deltaTime);
}  // namespace features::ability::systems