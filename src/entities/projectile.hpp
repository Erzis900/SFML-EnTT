#include "entt/entt.hpp"

namespace common::entities
{
    entt::entity createProjectile(entt::registry &registry, common::components::position &start, common::components::direction &dir);
}