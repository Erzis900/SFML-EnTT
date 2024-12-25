#include "enemy.hpp"
#include "entities/unit.hpp"
#include "components/shape.hpp"
#include "features/enemy/components/aiControlled.hpp"

#include <SFML/Graphics.hpp>
#include <random>

float randomFloat(float min, float max)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

namespace features::enemy::entities
{
    entt::entity createEnemy(entt::registry &registry)
    {
        auto entity = registry.create();

        float minX = 100.f, maxX = 1000.f;
        float minY = 100.f, maxY = 600.f;

        sf::Vector2f pos = { randomFloat(minX, maxX), randomFloat(minY, maxY) };

        sf::CircleShape enemyShape(50.f);
        enemyShape.setFillColor(sf::Color::Red);
        enemyShape.setOrigin(enemyShape.getRadius(), enemyShape.getRadius());

        float speed = 50.f;
        createUnit(registry, entity, pos, speed);

        registry.emplace<common::components::shape>(entity, enemyShape);
        registry.emplace<features::enemy::components::aiControlled>(entity, true);

        return entity;
    }
}