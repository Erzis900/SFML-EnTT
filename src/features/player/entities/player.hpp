#pragma once
#include "pch.hpp"

#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/healthRegen.hpp"
#include "components/renderable.hpp"
#include "components/unit.hpp"
#include "features/ability/entities/ability.hpp"
#include "features/item/components/equipped.hpp"
#include "features/item/entities/item.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/player/components/camera.hpp"
#include "features/player/components/initialCooldown.hpp"
#include "features/player/components/playerControlled.hpp"
#include "features/unit/loader/unitsLoader.hpp"
namespace features::player::entities
{
	entt::entity createPlayer(entt::registry &registry, item::ItemsLoader &itemsLoader, unit::UnitsLoader &unitsLoader);
}