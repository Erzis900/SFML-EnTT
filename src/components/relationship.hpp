#pragma once

#include "pch.hpp"

namespace common::components
{
	struct relationship
	{
		std::size_t children{};
		entt::entity first_child{entt::null};
		entt::entity prev{entt::null};
		entt::entity next{entt::null};
		entt::entity parent{entt::null};
		entt::entity source{entt::null};
	};
}  // namespace common::components
