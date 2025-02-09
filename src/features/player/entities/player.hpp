#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/healthRegen.hpp"
#include "components/renderable.hpp"
#include "components/shape.hpp"
#include "config.hpp"
#include "entities/unit.hpp"
#include "features/ability/entities/ability.hpp"
#include "features/item/components/equipped.hpp"
#include "features/item/entities/item.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/player/components/initialCooldown.hpp"
#include "features/player/components/playerControlled.hpp"
#include "pch.hpp"

namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, Config config, features::item::ItemsLoader &itemsLoader);
}