#include "moveEntities.hpp"
#include "components/direction.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "systems/moveEntities.hpp"

namespace common::systems
{
	void moveEntities(entt::registry &registry, float deltaTime)
	{
		auto view = registry.view<common::components::position, common::components::speed, common::components::direction>();

		for (auto [entity, pos, speed, dir] : view.each())
		{
			registry.replace<common::components::position>(entity, pos.x + dir.x * speed.value * deltaTime, pos.y + dir.y * speed.value * deltaTime);
		}
	}
}  // namespace common::systems
