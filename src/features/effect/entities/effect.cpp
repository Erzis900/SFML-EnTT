#include "effect.hpp"
#include "components/target.hpp"
#include "features/effect/components/effect.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects id, entt::entity target)
	{
		auto entity = registry.create();
		registry.emplace<common::components::target>(entity, target);
		registry.emplace<components::effect>(entity, id, effectsLoader.getEffect(id).duration, effectsLoader.getEffect(id).stacks,
											 effectsLoader.getEffect(id).refresh);
		return entity;
	}

	bool applyEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects id, entt::entity target)
	{
		auto effectsCount = registry.get<components::effects>(target).effectsCount;
		auto count = effectsCount[id];
		auto effect = effectsLoader.getEffect(id);
		if (count >= effect.stacks)
		{
			return false;
		}

		auto entity = createEffect(registry, effectsLoader, id, target);
		registry.emplace<components::affected>(entity, target, effect.duration);
		registry.emplace<common::components::renderable>(entity);

		auto attributes = registry.get<common::entities::Attributes>(target);
		common::entities::applyModifiers(registry, entity, attributes, effect.modifiers);
		effectsCount[id] = count + 1;
		registry.replace<components::effects>(target, effectsCount);
		return true;
	}

	bool removeEffect(entt::registry &registry, EffectsLoader &effectsLoader, entt::entity effectEntity)
	{
		auto id = registry.get<components::effect>(effectEntity).id;
		auto effect = effectsLoader.getEffect(id);

		auto affected = registry.get<components::affected>(effectEntity);

		auto effectsCount = registry.get<components::effects>(affected.target).effectsCount;
		auto count = effectsCount[id];
		effectsCount[id] = count - 1;
		registry.replace<components::effects>(affected.target, effectsCount);

		auto &attributes = registry.get<common::entities::Attributes>(affected.target);
		common::entities::removeModifiers(registry, effectEntity, attributes, effect.modifiers);

		// registry.destroy(effectEntity);
		return true;
	}

	bool removeEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects effectType, entt::entity target) { return false; }
}  // namespace features::effect::entities