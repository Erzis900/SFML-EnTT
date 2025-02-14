#pragma once

#include "../loader/animationLoader.hpp"
#include "pch.hpp"

namespace features::animation::systems
{
	void removeAnimation(entt::registry &registry, features::animation::AnimationLoader &animationLoader);
}