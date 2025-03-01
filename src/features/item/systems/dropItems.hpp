#pragma once
#include "../loader/itemsLoader.hpp"
#include "pch.hpp"

namespace features::item::systems
{
	void dropItems(entt::registry &registry, ItemsLoader &itemsLoader);
}