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

		auto view = registry.view<components::playerControlled, common::components::position, common::components::direction>();
		for (auto [entityUnit, pos, direction] : view.each())
		{
			sf::Vector2f dirVec = {mousePos.x - pos.x, mousePos.y - pos.y};
			dirVec = utils::normalize(dirVec);

			registry.replace<common::components::direction>(entityUnit, dir.x, dir.y, direction.movable);
			registry.replace<common::components::lookDirection>(entityUnit, dirVec.x, dirVec.y);
			registry.replace<common::components::pointsAt>(entityUnit, mousePos);

			for (auto [key, slotType] : keyToSlotType)
			{
				if (inputManager.isKeyPressed(key))
				{
					ability::entities::createEvent(registry, slotType, ability::components::castEvent::State::Press, mousePos, entityUnit);
				}
				else if (inputManager.isKeyHeld(key))
				{
					ability::entities::createEvent(registry, slotType, ability::components::castEvent::State::Hold, mousePos, entityUnit);
				}
				else if (inputManager.isKeyReleased(key))
				{
					ability::entities::createEvent(registry, slotType, ability::components::castEvent::State::Release, mousePos, entityUnit);
				}
			}
		}
	}
}  // namespace features::player::systems
