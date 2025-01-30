#pragma once

namespace features::player::components
{
	struct initialCooldown
	{
		float time;
		initialCooldown(float _time)
			: time(_time)
		{
		}
	};
}  // namespace features::player::components