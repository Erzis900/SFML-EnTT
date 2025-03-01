#pragma once
#include "features/player/managers/inputManager.hpp"
#include "pch.hpp"

namespace features::npc::systems
{
	void checkInteraction(entt::registry &registry, sf::RenderWindow &window, player::InputManager &inputManager);
}