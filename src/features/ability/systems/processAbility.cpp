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
		auto viewEvents = registry.view<components::castEvent>();
		for (auto [entityEvent, castEvent] : viewEvents.each())
		{
			for (auto [entity, rdy, ability] : view.each())
			{
				if (ability.source == castEvent.unit && ability.slot == castEvent.slot)
				{
					if (castEvent.state == components::castEvent::State::Press || castEvent.state == components::castEvent::State::Hold)
					{
						registry.remove<components::ready>(entity);
						registry.emplace<components::cast>(entity, ability.castTime);
					}
				}
			}
		}
	}

	void processCast(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<components::cast, components::ability, common::entities::Attributes>();

		for (auto [entity, cast, ability, attributes] : view.each())
		{
			cast.time -= deltaTime;

			if (cast.time <= 0.f)
			{
				auto &trigger = registry.get<common::components::attribute>(attributes.entities[common::entities::Stat::Trigger]);
				entt::entity hitbox;
				switch (static_cast<int>(trigger.value))
				{
				case features::item::Trigger::OnAttack:
				case features::item::Trigger::OnShot:
				case features::item::Trigger::OnCast:
					hitbox = features::hitbox::entities::createHitbox(registry, entity);
					spdlog::debug("Hitbox entity created, ID {}", static_cast<int>(hitbox));
					break;
				case features::item::Trigger::OnRoll:
				case features::item::Trigger::OnDash:
				case features::item::Trigger::OnBlink:
					break;
				default:
					break;
				}

				registry.remove<components::cast>(entity);
				registry.emplace<components::active>(entity, ability.activeTime);
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
				registry.emplace<components::delay>(entity, ability.delayTime);
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
