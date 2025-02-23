#include "processInvalid.hpp"
#include "components/remove.hpp"
#include "components/target.hpp"

namespace common::systems
{
	void processInvalid(entt::registry &registry)
	{
		auto view = registry.view<common::components::target>();

		for (auto [entity, target] : view.each())
		{
			if (!registry.valid(target.entity))
			{
				registry.emplace<common::components::remove>(entity);
			}
		}
	}
}  // namespace common::systems