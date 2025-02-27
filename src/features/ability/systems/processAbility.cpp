#include "processAbility.hpp"
#include "features/player/components/roll.hpp"
#include "utils.hpp"

namespace features::ability::systems
{
	void processAbility(entt::registry &registry, float deltaTime)
	{
		processReady(registry);
		processCast(registry, deltaTime);
		processActive(registry, deltaTime);
		processDelay(registry, deltaTime);
		processCooldown(registry, deltaTime);
		processRoll(registry, deltaTime);
	}

	void processReady(entt::registry &registry)
	{
		auto view = registry.view<components::ready, components::ability>();
		auto viewEvents = registry.view<components::castEvent, components::pointsAt>();
		for (auto [entityEvent, castEvent, pointsAt] : viewEvents.each())
		{
			for (auto [entity, rdy, ability] : view.each())
			{
				if (ability.source == castEvent.unit && ability.slot == castEvent.slot)
				{
					if (castEvent.state == components::castEvent::State::Press || castEvent.state == components::castEvent::State::Hold)
					{
						auto dir = registry.get<common::components::direction>(ability.source);
						registry.replace<common::components::direction>(ability.source, dir.x, dir.y, false);
						registry.remove<components::ready>(entity);
						registry.emplace<components::cast>(entity, ability.castTime);
						registry.emplace_or_replace<components::pointsAt>(entity, pointsAt.target);
					}
				}
			}
		}
	}

	void processCastCancel(entt::registry &registry)
	{
		auto viewCasts = registry.view<components::cast, components::ability>();
		auto viewEvents = registry.view<components::castEvent>();
		for (auto [entityEvent, castEvent] : viewEvents.each())
		{
			for (auto [entity, cast, ability] : viewCasts.each())
			{
				if (ability.source == castEvent.unit)
				{
					auto cancelsCast = castEvent.state == components::castEvent::State::Press && castEvent.slot == features::item::components::SlotType::NoSlot;
					if (cancelsCast)
					{
						auto dir = registry.get<common::components::direction>(ability.source);
						registry.replace<common::components::direction>(ability.source, dir.x, dir.y, true);

						registry.remove<components::cast>(entity);
						registry.emplace<components::ready>(entity);
					}
				}
			}
		}
	}

	void processRoll(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<player::components::roll, common::components::position>();
		for (auto [entity, roll, position] : view.each())
		{
			roll.currentTime += deltaTime;

			if (roll.currentTime >= roll.duration)
			{
				registry.remove<player::components::roll>(entity);
			}
			else
			{
				float t = roll.currentTime / roll.duration;
				float newX = utils::lerp(roll.startX, roll.targetX, t);
				float newY = utils::lerp(roll.startY, roll.targetY, t);
				registry.replace<common::components::position>(entity, newX, newY);
			}
		}
	}

	void processCast(entt::registry &registry, float deltaTime)
	{
		processCastCancel(registry);
		auto view = registry.view<components::cast, components::ability, components::pointsAt, common::entities::Attributes>();
		for (auto [entity, cast, ability, pointsAt, attributes] : view.each())
		{
			if (registry.valid(ability.source))
			{
				cast.time -= deltaTime;

				if (cast.time <= 0.f)
				{
					auto &trigger = registry.get<common::components::attribute>(attributes.entities[common::entities::Stat::Trigger]);
					entt::entity hitbox;
					switch (static_cast<int>(trigger.value))
					{
					case features::item::Trigger::OnAttack:
						break;
					case features::item::Trigger::OnShot:
						break;
					case features::item::Trigger::OnCast:
						hitbox = features::hitbox::entities::createHitbox(registry, entity);
						spdlog::debug("Hitbox entity created, ID {}", static_cast<int>(hitbox));
						break;
					case features::item::Trigger::OnRoll: {
						auto startPosition = registry.get<common::components::position>(ability.source);
						registry.emplace_or_replace<player::components::roll>(ability.source, startPosition.x, startPosition.y, pointsAt.target.x,
																			  pointsAt.target.y, 0.f, ability.activeTime);
						break;
					}
					case features::item::Trigger::OnDash:
						break;
					case features::item::Trigger::OnBlink:
						spdlog::debug("Blinked entity {} to ({},{})", static_cast<int>(ability.source), pointsAt.target.x, pointsAt.target.y);
						registry.replace<common::components::position>(ability.source, pointsAt.target.x, pointsAt.target.y);
						break;
					default:
						break;
					}

					registry.remove<components::cast>(entity);
					registry.emplace<components::active>(entity, ability.activeTime);
					auto dir = registry.get<common::components::direction>(ability.source);
					registry.replace<common::components::direction>(ability.source, dir.x, dir.y, true);
				}
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
