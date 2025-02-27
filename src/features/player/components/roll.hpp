#pragma once

namespace features::player::components
{
	struct roll
	{
		float startX, startY;
		float targetX, targetY;
		float currentTime, duration;
	};
}  // namespace features::player::components