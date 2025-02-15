#pragma once

#include "components/collider.hpp"
#include "components/faction.hpp"
#include "components/renderable.hpp"
#include "features/ability/entities/ability.hpp"
#include "features/enemy/components/aiControlled.hpp"
#include "features/item/components/equipped.hpp"
#include "features/item/entities/item.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/unit/loader/unitsLoader.hpp"
#include "pch.hpp"

namespace features::enemy::entities
{
	entt::entity createEnemy(entt::registry &registry, features::item::ItemsLoader &itemsLoader, features::unit::UnitsLoader &unitsLoader);
}