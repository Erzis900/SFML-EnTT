#include "playerShoot.hpp"

#include "components/cooldown.hpp"
#include "components/faction.hpp"
#include "components/position.hpp"
#include "features/hitbox/entities/hitbox.hpp"

#include "../components/cooldown.hpp"
#include "../components/playerControlled.hpp"

namespace features::player::systems
{
	void playerShoot(entt::registry &registry, sf::RenderWindow &window)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			auto view = registry.view<common::components::position, features::player::components::playerControlled, features::player::components::cooldown,
									  common::components::faction>();
			auto playerEntity = *view.begin();

			if (!registry.all_of<common::components::cooldown>(playerEntity))
			{
				auto &playerPos = view.get<common::components::position>(playerEntity);
				auto &playerCd = view.get<features::player::components::cooldown>(playerEntity);

				sf::Vector2f mousePos = (sf::Vector2f) sf::Mouse::getPosition(window);
				sf::Vector2f dirVec = {mousePos.x - playerPos.x, mousePos.y - playerPos.y};

				float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
				if (magnitude > 0)
				{
					dirVec.x /= magnitude;
					dirVec.y /= magnitude;
				}

				common::components::direction dir(dirVec.x, dirVec.y);
				common::entities::createHitbox(registry, playerEntity, dir);
				registry.emplace<common::components::cooldown>(playerEntity, playerCd.value);
			}
		}
	}
}  // namespace features::player::systems