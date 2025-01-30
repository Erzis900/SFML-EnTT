#include "followPlayer.hpp"

namespace features::enemy::systems
{
	void followPlayer(entt::registry &registry)
	{
		auto playerView = registry.view<features::player::components::playerControlled, common::components::position>();
		auto playerEntity = *playerView.begin();

		auto &playerPos = playerView.get<common::components::position>(playerEntity);

		auto enemyView = registry.view<features::enemy::components::aiControlled, common::components::position>();

		for (auto enemyEntity : enemyView)
		{
			auto &enemyPos = enemyView.get<common::components::position>(enemyEntity);
			// std::cout << enemyPos.x << " " << enemyPos.y << std::endl;

			sf::Vector2f dirVec = {playerPos.x - enemyPos.x, playerPos.y - enemyPos.y};

			float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
			if (magnitude > 0)
			{
				dirVec.x /= magnitude;
				dirVec.y /= magnitude;
			}

			common::components::direction dir(dirVec.x, dirVec.y);
			common::components::lookDirection lookDir(dirVec.x, dirVec.y);

			registry.replace<common::components::direction>(enemyEntity, dir);
			registry.replace<common::components::lookDirection>(enemyEntity, lookDir);
			// std::cout << dir.x << " " << dir.y << std::endl;
		}
	}
}  // namespace features::enemy::systems