#pragma once

#include "../components/ability.hpp"
#include "../components/ready.hpp"
#include "entities/attribute.hpp"

#include "pch.hpp"

namespace features::ability::entities
{
	entt::entity createAbility(entt::registry &registry, entt::entity source, float castTime, float activeTime, float delayTime, float cooldown);
}  // namespace features::ability::entities