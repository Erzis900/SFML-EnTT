#include "processPhysics.hpp"
#include "components/collider.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "features/player/components/playerControlled.hpp"

namespace common::systems
{
	void processPhysics(entt::registry &registry, float deltaTime, sf::Vector2i mapDim, sf::RenderWindow &window)
	{
		auto view = registry.view<common::components::position, common::components::collider, common::components::speed>();

		for (auto itA = view.begin(); itA != view.end(); ++itA)
		{
			auto entityA = *itA;
			auto &posA = view.get<common::components::position>(entityA);
			auto &collA = view.get<common::components::collider>(entityA);
			auto &speedA = view.get<common::components::speed>(entityA);

			if (registry.all_of<features::player::components::playerControlled>(entityA))
			{
				if (posA.x < window.getSize().x / 2) posA.x = window.getSize().x / 2;
				if (posA.y < window.getSize().y / 2) posA.y = window.getSize().y / 2;
				if (posA.x > mapDim.x) posA.x = mapDim.x;
				if (posA.y > mapDim.y) posA.y = mapDim.y;

				registry.replace<common::components::position>(entityA, posA.x, posA.y);
			}

			for (auto itB = std::next(itA); itB != view.end(); ++itB)
			{
				auto entityB = *itB;
				auto &posB = view.get<common::components::position>(entityB);
				auto &collB = view.get<common::components::collider>(entityB);
				auto &speedB = view.get<common::components::speed>(entityB);

				float deltaX = posB.x - posA.x;
				float deltaY = posB.y - posA.y;
				float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);

				if (distance < (collA.radius + collB.radius))
				{
					sf::Vector2f dirVec = {posA.x - posB.x, posA.y - posB.y};

					float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
					if (magnitude > 0)
					{
						dirVec.x /= magnitude;
						dirVec.y /= magnitude;
					}
					registry.replace<common::components::position>(entityA, posA.x + dirVec.x * speedA.value * deltaTime,
																   posA.y + dirVec.y * speedA.value * deltaTime);
					registry.replace<common::components::position>(entityB, posB.x - dirVec.x * speedB.value * deltaTime,
																   posB.y - dirVec.y * speedB.value * deltaTime);
				}
			}
		}
	}
}  // namespace common::systems