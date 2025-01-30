#pragma once

#include "../components/hitbox.hpp"
#include "components/area.hpp"
#include "components/damage.hpp"
#include "components/direction.hpp"
#include "components/faction.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/source.hpp"
#include "components/speed.hpp"

#include "pch.hpp"

namespace common::entities
{
	entt::entity createHitbox(entt::registry &registry, entt::entity source, float &x, float &y);
}