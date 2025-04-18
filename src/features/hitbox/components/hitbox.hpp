#pragma once
#include "pch.hpp"

namespace features::hitbox::components
{
	struct hitbox
	{
		float hitCount;
		std::vector<entt::entity> entities;
		std::vector<entt::entity> doneEntities;
	};
}  // namespace features::hitbox::components
