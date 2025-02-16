#include "checkTileCollision.hpp"
#include "../components/rectCollider.hpp"
#include "components/position.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::map::systems
{
	void checkTileCollision(entt::registry &registry, float deltaTime)
	{
		auto playerView = registry.view<features::player::components::playerControlled>();
		if (playerView.empty()) return;

		entt::entity entityA = *playerView.begin();

		auto &posA = registry.get<common::components::position>(entityA);
		auto &collA = registry.get<features::map::components::rectCollider>(entityA);

		sf::FloatRect rectA({posA.x - collA.width / 2, posA.y - collA.height / 2}, {collA.width, collA.height});

		auto view =
			registry.view<common::components::position, features::map::components::rectCollider>(entt::exclude<features::player::components::playerControlled>);

		for (auto [entityB, posB, collB] : view.each())
		{
			sf::FloatRect rectB({posB.x - collB.width / 2, posB.y - collB.height / 2}, {collB.width, collB.height});

			if (rectA.findIntersection(rectB))
			{
				sf::Vector2f dirVec = {posA.x - posB.x, posA.y - posB.y};

				float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
				if (magnitude > 0)
				{
					dirVec /= magnitude;
					registry.replace<common::components::position>(entityA, posA.x + dirVec.x * 200.f * deltaTime, posA.y + dirVec.y * 200.f * deltaTime);
				}
			}
		}
	}
}  // namespace features::map::systems