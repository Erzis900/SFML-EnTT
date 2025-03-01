#include "dropItems.hpp"
#include "../components/dropSpread.hpp"
#include "../components/dropped.hpp"
#include "../components/equipped.hpp"
#include "../components/itemId.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"
#include "utils.hpp"

namespace features::item::systems
{
	void dropItems(entt::registry &registry, ItemsLoader &itemsLoader)
	{
		auto view =
			registry.view<item::components::itemId, common::components::position, item::components::dropSpread>(entt::exclude<item::components::dropped>);
		for (auto [item, itemId, position, dropSpread] : view.each())
		{
			float dropChance = itemsLoader.getItem(itemId.id).dropChance;
			float randomValue = utils::randomFloat(0.f, 100.f);

			if (dropChance < randomValue)
			{
				registry.emplace<common::components::remove>(item);
			}

			position.x += utils::randomFloat(-dropSpread.value, dropSpread.value);
			position.y += utils::randomFloat(-dropSpread.value, dropSpread.value);

			registry.emplace<item::components::dropped>(item);
		}
	}
}  // namespace features::item::systems