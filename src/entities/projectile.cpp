#include "components/position.hpp"
#include "components/source.hpp"
#include "components/direction.hpp"
#include "components/damage.hpp"
#include "components/speed.hpp"
#include "projectile.hpp"

#include <SFML/Graphics.hpp>

namespace common::entities
{
    entt::entity createProjectile(entt::registry &registry, components::position &start, components::direction &dir)
    {
        const auto projectile = registry.create();
        registry.emplace<components::source>(projectile, registry.create());
        registry.emplace<components::speed>(projectile, 500.f);
        registry.emplace<components::direction>(projectile, dir.x, dir.y);
        registry.emplace<components::position>(projectile, start.x, start.y);
        registry.emplace<components::damage>(projectile, 10.f);
        return projectile;
    }
}
