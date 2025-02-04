#pragma once

#include "../components/ability.hpp"
#include "../components/active.hpp"
#include "../components/cast.hpp"
#include "../components/cooldown.hpp"
#include "../components/delay.hpp"
#include "../components/ready.hpp"
#include "pch.hpp"

#include "components/lookDirection.hpp"
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
}  // namespace features::ability::systems