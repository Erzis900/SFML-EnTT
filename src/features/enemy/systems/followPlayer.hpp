#pragma once

#include "pch.hpp"

#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/pointsAt.hpp"
#include "components/position.hpp"
#include "features/ability/components/castEvent.hpp"
#include "features/ability/entities/event.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::enemy::systems
{
	void followPlayer(entt::registry &registry);
}