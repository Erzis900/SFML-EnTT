#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/renderable.hpp"
#include "config.hpp"
#include "entities/unit.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "pch.hpp"

namespace features::enemy::entities
{
	entt::entity createEnemy(entt::registry &registry, Config config, features::item::ItemsLoader &itemsLoader);
}