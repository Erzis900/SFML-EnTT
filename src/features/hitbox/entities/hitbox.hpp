#include "pch.hpp"
#include "components/direction.hpp"

namespace common::entities
{
    entt::entity createHitbox(entt::registry &registry, entt::entity source, common::components::direction &dir);
}