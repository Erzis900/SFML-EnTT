#include "enemy.hpp"
#include "entities/unit.hpp"
#include "components/shape.hpp"
#include "features/enemy/components/aiControlled.hpp"

#include <SFML/Graphics.hpp>

namespace features::enemy::entities
{
    entt::entity createEnemy(entt::registry &registry)
    {
        auto entity = registry.create();
        sf::Vector2f pos = { 800.f, 500.f };

        sf::CircleShape enemyShape(50.f);
        enemyShape.setFillColor(sf::Color::Red);
        enemyShape.setOrigin(enemyShape.getRadius(), enemyShape.getRadius());

        createUnit(registry, entity, pos);
        registry.emplace<common::components::shape>(entity, enemyShape);
        registry.emplace<features::enemy::components::aiControlled>(entity, true);

        return entity;
    }
}