#include "processAbility.hpp"
#include "components/range.hpp"
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
		auto view = registry.view<components::ready, components::ability, common::entities::Attributes>();
		auto viewEvents = registry.view<components::castEvent, common::components::pointsAt, components::slot>();
		auto viewTriggers = registry.view<components::castEvent, common::components::pointsAt, components::trigger>();
		for (auto [entity, ready, ability, attributes] : view.each())
		{
			auto &trigger = registry.get<common::components::attribute>(attributes.entities[common::entities::Stat::Trigger]);
			for (auto [entityEvent, castEvent, pointsAt, slot] : viewEvents.each())
			{
				if (ability.source == castEvent.unit && ability.slot == slot.slot)
				{
					if (castEvent.state == components::castEvent::State::Press || castEvent.state == components::castEvent::State::Hold)
					{
						auto dir = registry.get<common::components::direction>(ability.source);
						registry.replace<common::components::direction>(ability.source, dir.x, dir.y, false);
						registry.remove<components::ready>(entity);
						registry.emplace<components::cast>(entity, ability.castTime);
						registry.emplace<common::components::pointsAt>(entity, pointsAt.position);
					}
				}
			}
			// for (auto [entityEvent, castEvent, pointsAt, castTrigger] : viewTriggers.each())
			// {
			// 	if (ability.source == castEvent.unit)
			// 	{
			// 		if (castTrigger.trigger == static_cast<item::Trigger>(trigger.value))
			// 		{
			// 			auto dir = registry.get<common::components::direction>(ability.source);
			// 			registry.replace<common::components::direction>(ability.source, dir.x, dir.y, false);
			// 			registry.remove<components::ready>(entity);
			// 			registry.emplace<components::cast>(entity, ability.castTime);
			// 			registry.emplace<common::components::pointsAt>(entity, pointsAt.position);
			// 		}
			// 	}
			// }
		}
	}

	void processCastCancel(entt::registry &registry)
	{
		auto viewCasts = registry.view<components::cast, components::ability>();
		auto viewEvents = registry.view<components::castEvent, components::slot>();
		for (auto [entityEvent, castEvent, slot] : viewEvents.each())
		{
			for (auto [entity, cast, ability] : viewCasts.each())
			{
				if (ability.source == castEvent.unit)
				{
					auto cancelsCast = castEvent.state == components::castEvent::State::Press && slot.slot == item::components::SlotType::NoSlot;
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
			static float currentTime = 0.f;
			currentTime += deltaTime;

			if (currentTime >= roll.duration)
			{
				registry.remove<player::components::roll>(entity);
				currentTime = 0.f;
			}
			else
			{
				float t = currentTime / roll.duration;
				float newX = utils::lerp(roll.startX, roll.targetX, t);
				float newY = utils::lerp(roll.startY, roll.targetY, t);
				registry.replace<common::components::position>(entity, newX, newY);
			}
		}
	}

	void processCast(entt::registry &registry, float deltaTime)
	{
		processCastCancel(registry);
		auto view = registry.view<components::cast, components::ability, common::components::pointsAt, common::entities::Attributes>();
		for (auto [entity, cast, ability, pointsAt, attributes] : view.each())
		{
			if (registry.valid(ability.source))
			{
				cast.time -= deltaTime;

				if (cast.time <= 0.f)
				{
					auto &trigger = registry.get<common::components::attribute>(attributes.entities[common::entities::Stat::Trigger]);
					entt::entity hitbox;
					switch (static_cast<item::Trigger>(trigger.value))
					{
					case item::Trigger::OnAttack:
					case item::Trigger::OnShot:
					case item::Trigger::OnCast:
					case item::Trigger::OnHit:
						hitbox = hitbox::entities::createHitbox(registry, entity);
						spdlog::debug("Hitbox entity created, ID {}", static_cast<int>(hitbox));
						break;
					case item::Trigger::OnRoll: {
						auto startPosition = registry.get<common::components::position>(ability.source);
						auto range = registry.get<common::components::range>(ability.source);

						float dirX = pointsAt.position.x - startPosition.x;
						float dirY = pointsAt.position.y - startPosition.y;
						sf::Vector2f dir = utils::normalize({dirX, dirY});

						float targetX = startPosition.x + dir.x * range.value;
						float targetY = startPosition.y + dir.y * range.value;

						registry.emplace_or_replace<player::components::roll>(ability.source, startPosition.x, startPosition.y, targetX, targetY,
																			  ability.activeTime);
						break;
					}
					case item::Trigger::OnDash:
					case item::Trigger::OnBlink:
						spdlog::debug("Blinked entity {} to ({},{})", static_cast<int>(ability.source), pointsAt.position.x, pointsAt.position.y);
						registry.replace<common::components::position>(ability.source, pointsAt.position.x, pointsAt.position.y);
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
				registry.remove<common::components::pointsAt>(entity);
				registry.emplace<components::ready>(entity);
			}
		}
	}
}  // namespace features::ability::systems
