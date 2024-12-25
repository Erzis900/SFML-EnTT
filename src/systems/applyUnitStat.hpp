// filepath: /c:/Users/piotr/Projects/SFML-EnTT/include/systems/applyUnitStat.hpp
#ifndef APPLY_UNIT_STAT_HPP
#define APPLY_UNIT_STAT_HPP

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

#endif // APPLY_UNIT_STAT_HPP