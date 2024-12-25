#pragma once

#include "external/entt.hpp"

#include "components/attribute.hpp"
#include "components/relationship.hpp"
#include "components/recalculate.hpp"
#include "components/modifiers.hpp"

#include "entities/attribute.hpp"

namespace common::systems
{
    void recalculateStat(entt::registry &registry);
}
