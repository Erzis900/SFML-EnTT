#include "playerShoot.hpp"

namespace features::player::systems
{
	void playerShoot(entt::registry &registry)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		{
			auto view =
				registry
					.view<features::player::components::playerControlled, features::player::components::initialCooldown, common::components::lookDirection>();
			auto playerEntity = *view.begin();

			if (!registry.all_of<common::components::cooldown>(playerEntity))
			{
				auto &lookDir = view.get<common::components::lookDirection>(playerEntity);
				auto &playerCd = view.get<features::player::components::initialCooldown>(playerEntity);

				common::entities::createHitbox(registry, playerEntity, lookDir.x, lookDir.y);
				registry.emplace<common::components::cooldown>(playerEntity, playerCd.time);
			}
		}
	}
}  // namespace features::player::systems