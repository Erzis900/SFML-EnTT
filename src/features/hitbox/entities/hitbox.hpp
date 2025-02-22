#pragma once

#include "components/area.hpp"
#include "components/attach.hpp"
#include "components/attribute.hpp"
#include "components/damage.hpp"
#include "components/direction.hpp"
#include "components/faction.hpp"
#include "components/lifespan.hpp"
#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "components/relationship.hpp"
#include "components/renderable.hpp"
#include "components/shape.hpp"
#include "components/source.hpp"
#include "components/speed.hpp"
#include "entities/attribute.hpp"

#include "features/ability/components/ability.hpp"
#include "features/item/loader/itemsLoader.hpp"

#include "../components/hitbox.hpp"

#include "pch.hpp"

namespace features::hitbox::entities
{
	entt::entity createHitbox(entt::registry &registry, entt::entity source);
}