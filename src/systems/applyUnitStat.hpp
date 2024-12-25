#pragma once

#include <array>

#include "external/entt.hpp"

#include "components/unit.hpp"
#include "components/speed.hpp"
#include "components/children.hpp"

#include "entities/attribute.hpp"

namespace common::systems
{
    void applyUnitStat(entt::registry &registry);
}
