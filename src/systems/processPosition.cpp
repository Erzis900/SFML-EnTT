#include "processPosition.hpp"

namespace common::systems
{
	void processPosition(entt::registry &registry, float deltaTime)
	{
		processMovable(registry);
		moveEntities(registry, deltaTime);
		attachEntities(registry);
	}

	void moveEntities(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<common::components::position, common::components::speed, common::components::direction>();

		for (auto [entity, pos, speed, dir] : view.each())
		{
			registry.replace<common::components::position>(entity, pos.x + dir.x * speed.value * deltaTime, pos.y + dir.y * speed.value * deltaTime);
		}
	}

	void processMovable(entt::registry &registry)
	{
		auto view = registry.view<common::components::direction>();
		for (auto [entity, dir] : view.each())
		{
			registry.replace<common::components::direction>(entity, dir.movable ? dir.x : 0.f, dir.movable ? dir.y : 0.f, dir.movable);
		}
	}

	void attachEntities(entt::registry &registry)
	{
		attachPosition(registry);
		attachDirection(registry);
	}

	void attachPosition(entt::registry &registry)
	{
		auto view = registry.view<common::components::attach, common::components::position>();

		for (auto [entity, attach, position] : view.each())
		{
			if (registry.valid(attach.target))
			{
				auto targetPosition = registry.get<components::position>(attach.target);
				registry.replace<components::position>(entity, targetPosition.x, targetPosition.y);
			}
		}
	}

	void attachDirection(entt::registry &registry)
	{
		auto view = registry.view<common::components::attach, common::components::direction>();

		for (auto [entity, attach, direction] : view.each())
		{
			if (registry.valid(attach.target))
			{
				auto targetDirection = registry.get<components::direction>(attach.target);
				registry.replace<components::direction>(entity, targetDirection.x, targetDirection.y, direction.movable);
			}
		}
	}
}  // namespace common::systems