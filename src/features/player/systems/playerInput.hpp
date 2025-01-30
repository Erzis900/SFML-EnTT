#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "features/player/components/playerControlled.hpp"

#include "pch.hpp"

namespace features::player::systems
{
	void playerInput(entt::registry &registry, sf::RenderWindow &window);
}