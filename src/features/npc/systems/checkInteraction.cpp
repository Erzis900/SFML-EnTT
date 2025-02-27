#include "checkInteraction.hpp"
#include "../components/npc.hpp"
#include "components/position.hpp"
#include "components/shape.hpp"
#include "player/components/playerControlled.hpp"
#include "utils.hpp"

namespace features::npc::systems
{
	void checkInteraction(entt::registry &registry, sf::RenderWindow &window, features::player::InputManager &inputManager)
	{
		auto npcView = registry.view<npc::components::npc, common::components::position, common::components::shape>();
		auto playerView = registry.view<player::components::playerControlled, common::components::position>();

		for (auto [npcEntity, npc, npcPos, shape] : npcView.each())
		{
			for (auto [playerEntity, playerControlled, playerPos] : playerView.each())
			{
				float distance = utils::getDistance({npcPos.x, npcPos.y}, {playerPos.x, playerPos.y});
				sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				// not optimal, okay for now (debugging)
				shape.shape.setFillColor(sf::Color::White);
				if (distance < 200.f)
				{
					// not optimal, okay for now (debugging)
					shape.shape.setFillColor(sf::Color::Cyan);
					if (shape.shape.getGlobalBounds().contains(mousePos) && inputManager.isButtonPressed(sf::Mouse::Button::Right))
					{
						npc.sound.play();
						spdlog::debug("Interacted with NPC");
					}
				}
			}
		}
	}
}  // namespace features::npc::systems