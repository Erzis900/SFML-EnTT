#pragma once

#include "pch.hpp"

namespace features::ability::components
{
	struct ability
	{
		entt::entity source;
		float castTime;
		float activeTime;
		float delayTime;
		float cooldownTime;
	};
}  // namespace features::ability::components
