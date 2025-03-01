#pragma once

#include "../loader/animationLoader.hpp"
#include "pch.hpp"

namespace features::animation::renderers
{
	void renderAnimations(entt::registry &registry, sf::RenderWindow &window, AnimationLoader &animationLoader);
}