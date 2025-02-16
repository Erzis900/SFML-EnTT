#pragma once

#include "pch.hpp"

namespace features::map::entities
{
	entt::entity createColliderTile(unsigned int id, int x, int y, int tileSize, float scalingFactor, entt::registry &registry);
}