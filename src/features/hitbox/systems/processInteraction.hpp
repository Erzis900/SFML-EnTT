#pragma once
#include "pch.hpp"

#include "components/attribute.hpp"
#include "components/health.hpp"
#include "components/pointsAt.hpp"
#include "components/source.hpp"
#include "entities/attribute.hpp"
#include "features/ability/entities/event.hpp"
#include "features/effect/entities/effect.hpp"

#include "../components/hitbox.hpp"

namespace features::hitbox::systems
{
	void processInteraction(entt::registry &registry, effect::EffectsLoader &effectsLoader);
}