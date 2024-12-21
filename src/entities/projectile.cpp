#include "entt/entt.hpp"
#include "components/position.hpp"
#include "components/source.hpp"
#include "components/direction.hpp"
#include "components/damage.hpp"
#include "components/speed.hpp"

namespace entities
{
    entt::entity createProjectile(entt::registry &registry)
    {
        const auto projectile = registry.create();
        registry.emplace<components::source>(projectile, registry.create());
        registry.emplace<components::speed>(projectile, 100.f);
        registry.emplace<components::direction>(projectile, 0.7f, 0.7f);
        registry.emplace<components::position>(projectile, 10.f, 10.f);
        registry.emplace<components::damage>(projectile, 10.f);
        return projectile;
    }
}
