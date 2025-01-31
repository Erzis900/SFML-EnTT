#pragma once

#include "components/health.hpp"
#include "components/position.hpp"
#include "components/remove.hpp"
#include "components/unit.hpp"
#include "features/item/components/equipped.hpp"
#include "features/item/components/itemId.hpp"
#include "pch.hpp"

namespace common::systems
{
	void processDeath(entt::registry &registry);
}