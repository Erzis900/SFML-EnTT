#pragma once

#include "components/children.hpp"
#include "components/direction.hpp"
#include "components/health.hpp"
#include "components/lookDirection.hpp"
#include "components/maxHealth.hpp"
#include "components/position.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/speed.hpp"
#include "components/unit.hpp"
#include "config.hpp"
#include "entities/attribute.hpp"
#include "features/item/entities/item.hpp"
#include "pch.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos, sf::Vector2f dir, float speed, float health, float maxHealth);