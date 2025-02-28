#include "dropItems.hpp"
#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"

namespace features::item::systems
{
	void dropItems(entt::registry &registry, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<item::components::itemId, common::components::position>();
		for (auto [item, itemId, position] : view.each())
		{
			float dropChance = itemsLoader.getItem(itemId.id).dropChance;
			// if (dropChance < 50.f)
			// {
			// 	registry.emplace<common::components::remove>(item);
			// }
			// spdlog::debug("{}", dropChance);
		}
	}
}  // namespace features::item::systems