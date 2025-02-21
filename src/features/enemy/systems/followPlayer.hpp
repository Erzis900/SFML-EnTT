#pragma once

#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "features/ability/components/castEvent.hpp"
#include "features/ability/components/pointsAt.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include "features/player/components/playerControlled.hpp"
#include "pch.hpp"

namespace features::enemy::systems
{
	void followPlayer(entt::registry &registry);
}