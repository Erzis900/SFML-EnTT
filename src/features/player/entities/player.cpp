#include "player.hpp"
#include "entities/unit.hpp"
#include "features/player/components/playerControlled.hpp"
#include "features/player/components/cooldown.hpp"
#include "components/shape.hpp"

namespace features::player::entities
{
    entt::entity createPlayer(entt::registry &registry, Config config)
    {
        auto entity = registry.create();

        sf::Vector2f pos = { config.startX, config.startY };

        sf::CircleShape playerShape(config.radius);
        playerShape.setFillColor(sf::Color::Yellow);
        playerShape.setOrigin(playerShape.getRadius(), playerShape.getRadius());

        createUnit(registry, entity, pos, config.speed);

        registry.emplace<features::player::components::playerControlled>(entity, true);
        registry.emplace<features::player::components::cooldown>(entity, config.cooldown);

        registry.emplace<common::components::shape>(entity, playerShape);

        return entity;
    }
}