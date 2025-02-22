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
			sf::Vector2f playerPos;
			if (registry.all_of<features::player::components::playerControlled>(entity))
			{
				playerPos = {registry.get<common::components::position>(entity).x, registry.get<common::components::position>(entity).y};
			}
			else
			{
				// std::cout << pos.x << " " << pos.y << std::endl;
				if (pos.x < playerPos.x - (window.getSize().x / 2) || pos.x > playerPos.x + (window.getSize().x / 2) ||
					pos.y < playerPos.y - (window.getSize().y / 2) || pos.y > playerPos.y + (window.getSize().y / 2))
				{
					registry.remove<common::components::visible>(entity);
				}
				else
				{
					registry.emplace_or_replace<common::components::visible>(entity);
					// spdlog::info("VISIBLE");
				}
			}
		}
	}
}  // namespace common::systems