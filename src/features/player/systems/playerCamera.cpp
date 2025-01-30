#include "playerCamera.hpp"
#include "components/position.hpp"
#include "features/player/components/camera.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::player::systems
{
	void playerCamera(entt::registry &registry, sf::RenderWindow &window)
	{
		auto view = registry.view<features::player::components::playerControlled, common::components::position, features::player::components::camera>();
		for (auto [entity, playerControlled, position, camera] : view.each())
		{
			camera.view.setCenter({position.x, position.y});
			camera.view.setSize({static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
			window.setView(camera.view);
			// std::cout << position.x << " " << position.y << std::endl;
		}
	}
}  // namespace features::player::systems