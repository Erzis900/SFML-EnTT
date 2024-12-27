#include "player.hpp"
#include "entities/unit.hpp"
#include "features/player/components/playerControlled.hpp"
#include "features/player/components/cooldown.hpp"
#include "components/shape.hpp"
#include "components/faction.hpp"
#include "components/healthRegen.hpp"

namespace features::player::entities
{
    entt::entity createPlayer(entt::registry &registry, Config config)
    {
        auto entity = registry.create();

        sf::CircleShape playerShape(config.player.radius);
        playerShape.setFillColor(sf::Color::Yellow);
        playerShape.setOrigin(playerShape.getRadius(), playerShape.getRadius());

        createUnit(registry, entity, {config.player.startX, config.player.startY}, {0, 0}, config.player.speed, config.player.health, config.player.maxHealth);

        registry.emplace<features::player::components::playerControlled>(entity, true);
        registry.emplace<features::player::components::cooldown>(entity, config.player.cooldown);

        registry.emplace<common::components::shape>(entity, playerShape);
        registry.emplace<common::components::faction>(entity, common::components::ALLY_MASK, common::components::ALLY_MASK, common::components::FOES_MASK);

        registry.emplace<common::components::healthRegen>(entity, config.player.healthRegen);

        return entity;
    }
}