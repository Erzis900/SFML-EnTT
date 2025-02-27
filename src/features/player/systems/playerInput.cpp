#include "playerInput.hpp"
#include "utils.hpp"

namespace features::player::systems
{
	void playerInput(entt::registry &registry, sf::RenderWindow &window, InputManager &inputManager)
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

		dir = utils::normalize(dir);

		auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

		auto view = registry.view<features::player::components::playerControlled, common::components::position, common::components::direction>();
		for (auto [entityUnit, playerControlled, pos, direction] : view.each())
		{
			sf::Vector2f dirVec = {mousePos.x - pos.x, mousePos.y - pos.y};
			dirVec = utils::normalize(dirVec);

			registry.replace<common::components::direction>(entityUnit, dir.x, dir.y, direction.movable);
			registry.emplace_or_replace<common::components::lookDirection>(entityUnit, dirVec.x, dirVec.y);

			for (auto [key, slotType] : keyToSlotType)
			{
				if (inputManager.isKeyPressed(key))
				{
					auto entityEvent = registry.create();
					registry.emplace<features::ability::components::castEvent>(entityEvent, entityUnit, slotType,
																			   features::ability::components::castEvent::State::Press);
					registry.emplace<features::ability::components::pointsAt>(entityEvent, mousePos);
				}
				else if (inputManager.isKeyHeld(key))
				{
					auto entityEvent = registry.create();
					registry.emplace<features::ability::components::castEvent>(entityEvent, entityUnit, slotType,
																			   features::ability::components::castEvent::State::Hold);
					registry.emplace<features::ability::components::pointsAt>(entityEvent, mousePos);
				}
				else if (inputManager.isKeyReleased(key))
				{
					auto entityEvent = registry.create();
					registry.emplace<features::ability::components::castEvent>(entityEvent, entityUnit, slotType,
																			   features::ability::components::castEvent::State::Release);
					registry.emplace<features::ability::components::pointsAt>(entityEvent, mousePos);
				}
			}
		}
	}
}  // namespace features::player::systems
