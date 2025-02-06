
#include "clearEvents.hpp"

namespace features::ability::systems
{
	void clearEvents(entt::registry &registry)
	{
		registry.view<features::ability::components::castEvent>().each([&registry](auto entity, auto &castEvent) { registry.destroy(entity); });
	}
}  // namespace features::ability::systems