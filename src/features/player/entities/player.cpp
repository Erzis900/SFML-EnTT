#include "player.hpp"
#include "entities/unit.hpp"
#include "features/player/components/playerControlled.hpp"
#include "features/player/components/cooldown.hpp"
#include "components/shape.hpp"

namespace features::player::entities
{
    entt::entity createPlayer(entt::registry &registry)
    {
        auto entity = registry.create();

        sf::Vector2f pos = { 200.f, 200.f };

        sf::CircleShape playerShape(50.f);
        playerShape.setFillColor(sf::Color::Yellow);
        playerShape.setOrigin(playerShape.getRadius(), playerShape.getRadius());

        float speed = 300.f;

        createUnit(registry, entity, pos, speed);

        registry.emplace<features::player::components::playerControlled>(entity, true);
        registry.emplace<features::player::components::cooldown>(entity, 0.1f);

        registry.emplace<common::components::shape>(entity, playerShape);

        return entity;
    }
}