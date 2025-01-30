#include "playerInput.hpp"

namespace features::player::systems
{
	sf::Vector2f normalize(const sf::Vector2f &vec)
	{
		float magnitude = std::sqrt(vec.x * vec.x + vec.y * vec.y);
		if (magnitude > 0)
		{
			return {vec.x / magnitude, vec.y / magnitude};
		}
		return vec;
	}

	void playerInput(entt::registry &registry, sf::RenderWindow &window)
	{
		sf::Vector2f dir = {0.f, 0.f};

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			dir.y = -1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			dir.y = 1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			dir.x = -1.f;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			dir.x = 1.f;
		}

		dir = normalize(dir);

		sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);

		auto view = registry.view<features::player::components::playerControlled, common::components::position>();
		for (auto [entity, playerControlled, pos] : view.each())
		{
			sf::Vector2f dirVec = {mousePos.x - pos.x, mousePos.y - pos.y};
			dirVec = normalize(dirVec);

			registry.replace<common::components::direction>(entity, dir.x, dir.y);
			registry.emplace_or_replace<common::components::lookDirection>(entity, dirVec.x, dirVec.y);
		}
	}
}  // namespace features::player::systems