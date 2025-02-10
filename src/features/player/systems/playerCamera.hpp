#include "pch.hpp"

sf::View getLetterboxView(sf::View view, int windowWidth, int windowHeight);

namespace features::player::systems
{
	void playerCamera(entt::registry &registry, sf::RenderWindow &window);
}  // namespace features::player::systems