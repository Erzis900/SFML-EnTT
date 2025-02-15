#pragma once
#include "pch.hpp"

#include "components/collider.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/shape.hpp"

namespace common::renderers
{
	void drawHealthbars(entt::registry &registry, sf::RenderWindow &window);
}