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
    entt::entity createEnemy(entt::registry &registry, Config config)
    {
        auto entity = registry.create();

        float minX = 100.f, maxX = 1000.f;
        float minY = 100.f, maxY = 600.f;

        sf::Vector2f pos = { randomFloat(minX, maxX), randomFloat(minY, maxY) };

        sf::CircleShape enemyShape(config.enemy.radius);
        enemyShape.setFillColor(sf::Color::Red);
        enemyShape.setOrigin(enemyShape.getRadius(), enemyShape.getRadius());

        createUnit(registry, entity, {pos.x, pos.y}, {0, 0}, config.enemy.speed, config.enemy.health, config.enemy.maxHealth);

        registry.emplace<features::enemy::components::aiControlled>(entity, true);
        registry.emplace<common::components::shape>(entity, enemyShape);

        return entity;
    }
}