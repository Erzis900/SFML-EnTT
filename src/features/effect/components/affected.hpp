#pragma once
#include "pch.hpp"

namespace features::effect::components
{
	struct affected
	{
		entt::entity target;
		float remainingTime;
	};

}  // namespace features::effect::components
