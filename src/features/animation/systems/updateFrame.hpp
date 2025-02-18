#pragma once

#include "../loader/animationLoader.hpp"
#include "pch.hpp"

namespace features::animation::systems
{
	void updateFrame(entt::registry &registry, float deltaTime);
}