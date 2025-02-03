#pragma once

#include "../components/ability.hpp"
#include "../components/active.hpp"
#include "../components/cast.hpp"
#include "../components/cooldown.hpp"
#include "../components/delay.hpp"
#include "../components/ready.hpp"
#include "pch.hpp"

#include "components/cooldown.hpp"
#include "components/lookDirection.hpp"
#include "features/hitbox/entities/hitbox.hpp"

#include "features/player/components/initialCooldown.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::ability::systems
{
	void processAbility(entt::registry &registry, float deltaTime);
}  // namespace features::ability::systems