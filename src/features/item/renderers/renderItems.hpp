#pragma once

#include "pch.hpp"

#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"
#include "components/renderable.hpp"
#include "components/unit.hpp"

#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "../loader/itemsLoader.hpp"

namespace features::item::renderers
{
	void renderItems(entt::registry &registry, sf::RenderWindow &window, ItemsLoader &itemsLoader);
	void renderEquippedItems(entt::registry &registry, sf::RenderWindow &window, ItemsLoader &itemsLoader);
	void renderGroundItems(entt::registry &registry, sf::RenderWindow &window, ItemsLoader &itemsLoader);
}  // namespace features::item::renderers
