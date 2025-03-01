#pragma once

#include "pch.hpp"

#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/unit.hpp"

#include "../loader/unitsLoader.hpp"

namespace features::unit::renderers
{
	void renderUnits(entt::registry &registry, sf::RenderWindow &window, UnitsLoader &unitsLoader);
}  // namespace features::unit::renderers
