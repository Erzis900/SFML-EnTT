#include "processVisibility.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/visible.hpp"
#include "features/player/components/playerControlled.hpp"

namespace common::systems
{
	void processVisibility(entt::registry &registry, sf::RenderWindow &window)
	{
		auto view = registry.view<common::components::renderable, common::components::position>();
		for (auto [entity, renderable, pos] : view.each())
		{
			static sf::Vector2f playerPos;
			if (registry.all_of<features::player::components::playerControlled>(entity))
			{
				playerPos = {registry.get<common::components::position>(entity).x, registry.get<common::components::position>(entity).y};
			}
			else
			{
				static sf::Vector2u windowSize = window.getSize();
				if (pos.x < playerPos.x - (windowSize.x / 2) || pos.x > playerPos.x + (windowSize.x / 2) || pos.y < playerPos.y - (windowSize.y / 2) ||
					pos.y > playerPos.y + (windowSize.y / 2))
				{
					registry.remove<common::components::visible>(entity);
				}
				else
				{
					registry.emplace_or_replace<common::components::visible>(entity);
				}
			}
			// std::cout << playerPos.x << " " << playerPos.y << std::endl;
			// std::cout << pos.x << " " << pos.y << std::endl;
		}
	}
}  // namespace common::systems