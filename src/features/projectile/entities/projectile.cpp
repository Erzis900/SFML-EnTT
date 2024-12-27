#include "components/source.hpp"
#include "components/damage.hpp"
#include "components/speed.hpp"
#include "components/area.hpp"
#include "components/renderable.hpp"
#include "../components/isProjectile.hpp"
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
        registry.emplace<features::projectile::components::isProjectile>(projectile, true);

        float radius = 10.f;
        sf::CircleShape projectileShape(radius);
        projectileShape.setFillColor(sf::Color::White);
        projectileShape.setOrigin(projectileShape.getRadius(), projectileShape.getRadius());

        registry.emplace<common::components::renderable>(projectile, projectileShape);
        registry.emplace<common::components::area>(projectile, radius);

        return projectile;
    }
}
