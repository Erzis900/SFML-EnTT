#pragma once

#include "features/item/components/equipped.hpp"
#include "pch.hpp"

namespace features::ability::components
{
	struct ability
	{
		entt::entity source;
		features::item::components::SlotType slot;
		float castTime;
		float activeTime;
		float delayTime;
		float cooldownTime;
	};
}  // namespace features::ability::components
