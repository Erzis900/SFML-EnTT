#pragma once

#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/position.hpp"
#include "components/unit.hpp"
#include "entities/attribute.hpp"

#include "pch.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos);