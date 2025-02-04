#include "processAbility.hpp"

namespace features::ability::systems
{
	void processAbility(entt::registry &registry, float deltaTime)
	{
		processReady(registry);
		processCast(registry, deltaTime);
		processActive(registry, deltaTime);
		processDelay(registry, deltaTime);
		processCooldown(registry, deltaTime);
	}

	void processReady(entt::registry &registry)
	{
		auto view = registry.view<components::ready, components::ability>();

		for (auto [entity, rdy, abi] : view.each())
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				registry.remove<components::ready>(entity);
				registry.emplace<components::cast>(entity, 0.05f);
			}
		}
	}

	void processCast(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::cast, components::ability>();

		for (auto [entity, cast, ability] : view.each())
		{
			cast.time -= deltaTime;

			if (cast.time <= 0.f)
			{
				auto view = registry.view<features::player::components::playerControlled, common::components::lookDirection>();
				auto playerEntity = *view.begin();

				auto &lookDir = view.get<common::components::lookDirection>(playerEntity);

				common::entities::createHitbox(registry, playerEntity, lookDir.x, lookDir.y);

				registry.remove<components::cast>(entity);
				registry.emplace<components::active>(entity, 0.025f);
			}
		}
	}

	void processActive(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::active, components::ability>();

		for (auto [entity, active, ability] : view.each())
		{
			active.time -= deltaTime;

			if (active.time <= 0.f)
			{
				registry.remove<components::active>(entity);
				registry.emplace<components::delay>(entity, ability.activeTime);
			}
		}
	}

	void processDelay(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::delay, components::ability>();

		for (auto [entity, delay, ability] : view.each())
		{
			delay.time -= deltaTime;

			if (delay.time <= 0.f)
			{
				registry.remove<components::delay>(entity);
				registry.emplace<components::cooldown>(entity, ability.cooldownTime);
			}
		}
	}

	void processCooldown(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::cooldown, components::ability>();

		for (auto [entity, cooldown, ability] : view.each())
		{
			cooldown.time -= deltaTime;

			if (cooldown.time <= 0.f)
			{
				registry.remove<components::cooldown>(entity);
				registry.emplace<components::ready>(entity);
			}
		}
	}
}  // namespace features::ability::systems
