#pragma once

#include "pch.hpp"

#include "components/attach.hpp"
#include "components/direction.hpp"
#include "components/position.hpp"

namespace common::systems
{
	void attachEntities(entt::registry &registry);
	void attachPosition(entt::registry &registry);
	void attachDirection(entt::registry &registry);
}  // namespace common::systems
