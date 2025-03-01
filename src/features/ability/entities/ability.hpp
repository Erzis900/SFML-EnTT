#pragma once

#include "../components/ability.hpp"
#include "../components/ready.hpp"
#include "entities/attribute.hpp"
#include "features/item/components/equipped.hpp"

#include "pch.hpp"

namespace features::ability::entities
{
	entt::entity createAbility(entt::registry &registry, entt::entity source, item::components::SlotType slotType, float castTime, float activeTime,
							   float delayTime, float cooldown);
}  // namespace features::ability::entities