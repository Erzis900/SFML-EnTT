#include "pch.hpp"
#include <SFML/Graphics.hpp>

#include "external/entt.hpp"

#include "components/position.hpp"
#include "features/item/loader/itemsLoader.hpp"

#include "components/direction.hpp"
#include "components/renderable.hpp"
#include "math.h"

namespace common::renderers
{
	void drawShapes(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader);
}