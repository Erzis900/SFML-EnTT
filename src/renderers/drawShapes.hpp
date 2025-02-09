#include "pch.hpp"

#include "components/direction.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/shape.hpp"
#include "features/item/loader/itemsLoader.hpp"

namespace common::renderers
{
	void drawShapes(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader);
}