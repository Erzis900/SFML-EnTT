#include "external/entt.hpp"
#include "components/position.hpp"
#include "components/direction.hpp"

namespace common::entities
{
    entt::entity createProjectile(entt::registry &registry, common::components::position &start, common::components::direction &dir);
}