#include "entt/entt.hpp"

namespace entities
{
    entt::entity createProjectile(entt::registry &registry, components::position &start, components::direction &dir);
}