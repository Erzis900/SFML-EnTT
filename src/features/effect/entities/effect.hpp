#pragma once
#include "../loader/effectLoader.hpp"
#include "pch.hpp"

namespace features::effect::entities
{
	entt::entity createEffect(entt::registry &registry, entt::entity &target, const std::string &effectName, features::effect::EffectLoader &effectLoader);
}