#pragma once
#include "../loader/effectLoader.hpp"
#include "pch.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, entt::entity target, features::effect::Type type, features::effect::EffectLoader &effectLoader);
}