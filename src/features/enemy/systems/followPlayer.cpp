#include "followPlayer.hpp"
#include "utils.hpp"

namespace features::enemy::systems
{
	void followPlayer(entt::registry &registry)
	{
		auto playerView = registry.view<features::player::components::playerControlled, common::components::position>();
		if (playerView.begin() == playerView.end())
		{
			return;
		}
		auto playerEntity = *playerView.begin();
		auto &playerPos = playerView.get<common::components::position>(playerEntity);
		sf::Vector2f targetPosition = {playerPos.x, playerPos.y};
		auto enemyView = registry.view<features::enemy::components::aiControlled, common::components::position, common::components::direction>();

		for (auto enemyEntity : enemyView)
		{
			auto &enemyPos = enemyView.get<common::components::position>(enemyEntity);
			auto direction = enemyView.get<common::components::direction>(enemyEntity);
			// std::cout << enemyPos.x << " " << enemyPos.y << std::endl;

			sf::Vector2f dirVec = {playerPos.x - enemyPos.x, playerPos.y - enemyPos.y};

			float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
			if (magnitude > 0)
			{
				dirVec.x /= magnitude;
				dirVec.y /= magnitude;
			}

			if (magnitude < 200)
			{
				auto entityEvent = registry.create();
				registry.emplace<features::ability::components::castEvent>(entityEvent, enemyEntity, features::item::components::SlotType::Mainhand,
																		   features::ability::components::castEvent::State::Press);
				registry.emplace<features::ability::components::pointsAt>(entityEvent, targetPosition);
			}

			registry.replace<common::components::direction>(enemyEntity, dirVec.x, dirVec.y, direction.movable);
			registry.replace<common::components::lookDirection>(enemyEntity, dirVec.x, dirVec.y);
			// std::cout << dir.x << " " << dir.y << std::endl;
		}
	}
}  // namespace features::enemy::systems