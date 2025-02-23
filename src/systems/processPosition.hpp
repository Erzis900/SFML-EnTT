#pragma once

#include "pch.hpp"

#include "components/attach.hpp"
#include "components/direction.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"

namespace common::systems
{
	void processPosition(entt::registry &registry, float deltaTime);

	void moveEntities(entt::registry &registry, float deltaTime);

	void processMovable(entt::registry &registry);

	void attachEntities(entt::registry &registry);

	void attachPosition(entt::registry &registry);

	void attachDirection(entt::registry &registry);
}  // namespace common::systems