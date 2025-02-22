#pragma once
#include "../loader/effectLoader.hpp"
#include "pch.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, features::effect::EffectLoader &effectLoader, features::effect::Effects id, entt::entity target);
}