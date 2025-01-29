#pragma once
#include "pch.hpp"

namespace features::item::components
{
	enum SlotType
	{
		Helmet = 0,
		Chest = 1,
		Shoulder = 2,
		Mainhand = 3,
		Offhand = 4,
		Cape = 5,
	};
	struct equipped
	{
		entt::entity unit;
		int itemId;
		SlotType slot;
		int coord;
	};

}  // namespace features::item::components
