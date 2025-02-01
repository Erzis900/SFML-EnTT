#pragma once
#include "pch.hpp"

namespace features::item::components
{
	enum SlotType
	{
		Head = 0,
		Chest = 1,
		MainShoulder = 2,
		OffShoulder = 3,
		Mainhand = 4,
		Offhand = 5,
		Cape = 6,
	};
	struct equipped
	{
		entt::entity unit;
		SlotType slot;
		int coord;
	};

}  // namespace features::item::components
