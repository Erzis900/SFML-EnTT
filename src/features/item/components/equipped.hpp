#pragma once
#include "pch.hpp"

namespace features::item::components
{
	enum SlotType
	{
		NoSlot = 0,
		Head = 1,
		Chest = 2,
		MainShoulder = 3,
		OffShoulder = 4,
		Mainhand = 5,
		Offhand = 6,
		Cape = 7,
	};
	struct equipped
	{
		entt::entity unit;
		SlotType slot;
	};

}  // namespace features::item::components
