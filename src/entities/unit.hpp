#pragma once

#include "config.hpp"
#include "features/item/entities/item.hpp"
#include "pch.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos, sf::Vector2f dir, float speed, float health, float maxHealth);