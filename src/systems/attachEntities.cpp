#include "attachEntities.hpp"

namespace common::systems
{
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
			auto targetPosition = registry.get<components::position>(attach.target);
			registry.replace<components::position>(entity, targetPosition.x, targetPosition.y);
		}
	}

	void attachDirection(entt::registry &registry)
	{
		auto view = registry.view<common::components::attach, common::components::direction>();

		for (auto [entity, attach, direction] : view.each())
		{
			auto targetDirection = registry.get<components::direction>(attach.target);
			registry.replace<components::direction>(entity, targetDirection.x, targetDirection.y);
		}
	}
}  // namespace common::systems
