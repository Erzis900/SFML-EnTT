#include "processAbility.hpp"

namespace features::ability::systems
{
	void processAbility(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::ready>();

		for (auto [entity] : view.each())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				registry.remove<components::ready>(entity);
				registry.emplace<components::cast>(entity, 0.05f);
			}
		}

		registry.view<components::cast>().each([&](auto entity, auto &cast) {
			cast.time -= deltaTime;

			if (cast.time <= 0.f)
			{
				auto view = registry.view<features::player::components::playerControlled, features::player::components::initialCooldown,
										  common::components::lookDirection>();
				auto playerEntity = *view.begin();

				if (!registry.all_of<common::components::cooldown>(playerEntity))
				{
					auto &lookDir = view.get<common::components::lookDirection>(playerEntity);
					auto &playerCd = view.get<features::player::components::initialCooldown>(playerEntity);

					common::entities::createHitbox(registry, playerEntity, lookDir.x, lookDir.y);
					registry.emplace<common::components::cooldown>(playerEntity, playerCd.time);
				}

				registry.remove<components::cast>(entity);
				registry.emplace<components::active>(entity, 0.025f);
			}
		});

		registry.view<components::active>().each([&](auto entity, auto &active) {
			active.time -= deltaTime;
			if (active.time <= 0.f)
			{
				registry.remove<components::active>(entity);
				registry.emplace<components::delay>(entity, 0.f);
			}
		});

		registry.view<components::delay>().each([&](auto entity, auto &delay) {
			delay.time -= deltaTime;
			if (delay.time <= 0.f)
			{
				registry.remove<components::delay>(entity);
				registry.emplace<components::cooldown>(entity, 0.05f);
			}
		});

		registry.view<components::cooldown>().each([&](auto entity, auto &cooldown) {
			cooldown.time -= deltaTime;
			if (cooldown.time <= 0.f)
			{
				registry.remove<components::cooldown>(entity);
				registry.emplace<components::ready>(entity);
			}
		});
	}
}  // namespace features::ability::systems
