#pragma once

namespace features::player::components
{
	struct playerControlled
	{
		bool isControlled;
		playerControlled(bool controlled)
			: isControlled(controlled)
		{
		}
	};

}  // namespace features::player::components
