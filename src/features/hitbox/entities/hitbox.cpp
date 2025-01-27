#include "hitbox.hpp"
#include "components/source.hpp"
#include "components/damage.hpp"
#include "components/speed.hpp"
#include "components/position.hpp"
#include "components/area.hpp"
#include "components/faction.hpp"
#include "components/renderable.hpp"
#include "../components/hitbox.hpp"

namespace common::entities
{
    entt::entity createHitbox(entt::registry &registry, entt::entity source, components::direction &dir)
    {
        const auto hitboxEntity = registry.create();
        registry.emplace<components::source>(hitboxEntity, source);
        registry.emplace<components::speed>(hitboxEntity, 500.f);
        auto pos = registry.get<components::position>(source);
        registry.emplace<components::direction>(hitboxEntity, dir.x, dir.y);
        registry.emplace<components::position>(hitboxEntity, pos.x, pos.y);
        registry.emplace<components::damage>(hitboxEntity, 10.f);
        auto &hitbox = registry.emplace<features::hitbox::components::hitbox>(hitboxEntity, .7f, .7f, 2.f, std::vector<entt::entity>(), std::vector<entt::entity>());
        auto faction = registry.get<common::components::faction>(source);
        registry.emplace<common::components::faction>(hitboxEntity, faction.affiliation, faction.allies, faction.foes);

        float radius = 10.f;
        sf::CircleShape hitboxShape(radius);
        hitboxShape.setFillColor(sf::Color::White);
        hitboxShape.setOrigin({hitboxShape.getRadius(), hitboxShape.getRadius()});

        registry.emplace<common::components::renderable>(hitboxEntity, hitboxShape);
        registry.emplace<common::components::area>(hitboxEntity, radius);

        return hitboxEntity;
    }
}
