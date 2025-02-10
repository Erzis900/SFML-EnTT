#include "playerCamera.hpp"
#include "components/position.hpp"
#include "features/player/components/camera.hpp"
#include "features/player/components/playerControlled.hpp"

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight)
{
	float windowRatio = static_cast<float>(windowWidth) / static_cast<float>(windowHeight);
	float viewRatio = view.getSize().x / static_cast<float>(view.getSize().y);
	float sizeX = 1.f;
	float sizeY = 1.f;
	float posX = 0.f;
	float posY = 0.f;

	bool horizontalSpacing = true;
	if (windowRatio < viewRatio) horizontalSpacing = false;

	if (horizontalSpacing)
	{
		sizeX = viewRatio / windowRatio;
		posX = (1 - sizeX) / 2.f;
	}
	else
	{
		sizeY = windowRatio / viewRatio;
		posY = (1 - sizeY) / 2.f;
	}

	view.setViewport(sf::FloatRect({posX, posY}, {sizeX, sizeY}));

	return view;
}

namespace features::player::systems
{
	void playerCamera(entt::registry &registry, sf::RenderWindow &window)
	{
		auto view = registry.view<features::player::components::playerControlled, common::components::position, features::player::components::camera>();
		for (auto [entity, playerControlled, position, camera] : view.each())
		{
			camera.view = window.getView();
			camera.view.setCenter({position.x, position.y});
			camera.view = getLetterboxView(camera.view, window.getSize().x, window.getSize().y);
			window.setView(camera.view);
			// std::cout << position.x << " " << position.y << std::endl;
		}
	}
}  // namespace features::player::systems