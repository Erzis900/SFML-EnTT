#pragma once

#include "pch.hpp"

namespace common::components
{
	struct source
	{
		entt::entity entity;
		source(entt::entity entity)
			: entity(entity)
		{
		}
	};
}  // namespace common::components
