#pragma once
#include "pch.hpp"

#include "../components/equipped.hpp"

namespace features::item::entities
{
	entt::entity equipItem(entt::registry &registry, entt::entity unit, int itemId, features::item::components::SlotType slot, int coord);
}