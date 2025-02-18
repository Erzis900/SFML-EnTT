#include "cleanupRemoved.hpp"
#include "components/remove.hpp"

namespace common::systems
{
	void cleanupRemoved(entt::registry &registry)
	{
		auto view = registry.view<common::components::remove>();

		for (auto [entity] : view.each())
		{
			registry.destroy(entity);
			spdlog::debug("Destroyed {}", static_cast<int>(entity));
		}
	}
}  // namespace common::systems
