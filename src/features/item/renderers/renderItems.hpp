#include "pch.hpp"

#include "components/direction.hpp"
#include "components/position.hpp"

#include "../components/equipped.hpp"
#include "../loader/itemsLoader.hpp"

namespace features::item::renderers
{
	void renderItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader);
}
