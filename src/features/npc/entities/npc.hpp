#pragma once
#include "pch.hpp"

namespace features::npc::entities
{
	entt::entity createNPC(entt::registry &registry, sf::Sound &sound);
}