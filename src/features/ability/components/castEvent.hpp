#pragma once

#include "features/item/components/equipped.hpp"

#include "pch.hpp"

namespace features::ability::components
{
	struct castEvent
	{
		entt::entity unit;
		features::item::components::SlotType slot;
		enum class State
		{
			Press,
			Release,
			Hold
		} state;
	};
}  // namespace features::ability::components