#pragma once
#include "pch.hpp"

#include "../components/affected.hpp"
#include "../entities/effect.hpp"
#include "../loader/effectsLoader.hpp"
#include "components/remove.hpp"

namespace features::effect::systems
{
	void processEffects(entt::registry &registry, float deltaTime, EffectsLoader &effectsLoader);
}