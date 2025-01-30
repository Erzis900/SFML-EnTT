#include "pch.hpp"

#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"
#include "components/unit.hpp"

#include "../components/equipped.hpp"
#include "../loader/itemsLoader.hpp"

namespace features::item::renderers
{
	void renderItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader);
}
