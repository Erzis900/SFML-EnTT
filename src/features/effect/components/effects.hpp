#pragma once

#include "pch.hpp"

#include "../models/effects.hpp"

namespace features::effect::components
{
	struct effects
	{
		std::map<features::effect::Effects, float> effectsCount;
	};
}  // namespace features::effect::components
