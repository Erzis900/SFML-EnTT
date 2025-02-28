#include "processDeath.hpp"
#include "features/item/components/dropSpread.hpp"
#include "features/player/components/playerControlled.hpp"

namespace common::systems
{
	void processDeath(entt::registry &registry, StateManager &stateManager)
	{
		auto view = registry.view<common::components::health>();

		for (auto [entity, health] : view.each())
		{
			if (health.value <= 0.f)
			{
				registry.emplace<common::components::remove>(entity);

				if (registry.all_of<features::player::components::playerControlled>(entity))
				{
					spdlog::info("Player died");
					stateManager.setState(State::Game, false);
					stateManager.setState(State::GameOver, true);
				}
			}
		}

		auto view_removed = registry.view<common::components::remove, common::components::unit>();
		std::set<entt::entity> removed_units = {};
		for (auto [entity, removed] : view_removed.each())
		{
			removed_units.insert(entity);
		}
		auto view_equipped = registry.view<features::item::components::equipped, features::item::components::itemId>();
		for (auto [entity, equipped, itemId] : view_equipped.each())
		{
			if (removed_units.find(equipped.unit) != removed_units.end())
			{
				registry.emplace<common::components::remove>(entity);
				auto itemEntity = registry.create();
				registry.emplace<features::item::components::itemId>(itemEntity, itemId.id);
				registry.emplace<common::components::position>(itemEntity, registry.get<common::components::position>(equipped.unit));
				registry.emplace<features::item::components::dropSpread>(itemEntity, 100.f);
			}
		}
	}
}  // namespace common::systems