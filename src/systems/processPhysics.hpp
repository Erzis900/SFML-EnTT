#pragma once

#include "pch.hpp"

namespace common::systems
{
	void processPhysics(entt::registry &registry, float deltaTime, sf::Vector2i mapDim, sf::RenderWindow &window);
}