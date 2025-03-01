#pragma once

#include "pch.hpp"

#include "components/modifiers.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/renderable.hpp"
#include "entities/attribute.hpp"

#include "../components/affected.hpp"
#include "../components/effect.hpp"
#include "../components/effects.hpp"
#include "../loader/effectsLoader.hpp"
#include "../models/effects.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects id, entt::entity target);

	bool applyEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects id, entt::entity target);
	bool removeEffect(entt::registry &registry, EffectsLoader &effectsLoader, entt::entity effectEntity);
	bool removeEffect(entt::registry &registry, EffectsLoader &effectsLoader, Effects effectType, entt::entity target);
}  // namespace features::effect::entities