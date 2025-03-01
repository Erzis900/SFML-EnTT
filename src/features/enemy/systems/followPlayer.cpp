#include "followPlayer.hpp"
#include "utils.hpp"

namespace features::enemy::systems
{
	void followPlayer(entt::registry &registry)
	{
		auto playerView = registry.view<player::components::playerControlled, common::components::position>();
		if (playerView.begin() == playerView.end())
		{
			return;
		}
		auto playerEntity = *playerView.begin();
		auto &playerPos = playerView.get<common::components::position>(playerEntity);
		sf::Vector2f targetPosition = {playerPos.x, playerPos.y};
		auto enemyView = registry.view<components::aiControlled, common::components::position, common::components::direction>();

		for (auto [enemyEntity, enemyPos, direction] : enemyView.each())
		{
			sf::Vector2f dirVec = {playerPos.x - enemyPos.x, playerPos.y - enemyPos.y};

			float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
			if (magnitude > 0)
			{
				dirVec.x /= magnitude;
				dirVec.y /= magnitude;
			}

			if (magnitude < 200)
			{
				ability::entities::createEvent(registry, item::components::SlotType::Mainhand, ability::components::castEvent::State::Press, targetPosition,
											   enemyEntity);
			}

			registry.replace<common::components::direction>(enemyEntity, dirVec.x, dirVec.y, direction.movable);
			registry.replace<common::components::lookDirection>(enemyEntity, dirVec.x, dirVec.y);
			registry.replace<common::components::pointsAt>(enemyEntity, targetPosition);
		}
	}
}  // namespace features::enemy::systems