#pragma once

#include "../models/effects.hpp"

namespace features::effect::components
{
	struct effect
	{
		Effects id;
		float duration;
		float stacks;
		bool refresh;
	};
}  // namespace features::effect::components