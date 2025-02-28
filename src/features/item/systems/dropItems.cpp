#include "dropItems.hpp"
#include "../components/dropped.hpp"
#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"
#include "utils.hpp"

namespace features::item::systems
{
	void dropItems(entt::registry &registry, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<item::components::itemId, common::components::position>(entt::exclude<item::components::dropped>);
		for (auto [item, itemId, position] : view.each())
		{
			float dropChance = itemsLoader.getItem(itemId.id).dropChance;
			float randomValue = utils::randomFloat(0.f, 100.f);

			// spdlog::debug("{} {}", dropChance, randomValue);

			if (dropChance < randomValue)
			{
				registry.emplace<common::components::remove>(item);
			}

			registry.emplace<item::components::dropped>(item);
		}
	}
}  // namespace features::item::systems