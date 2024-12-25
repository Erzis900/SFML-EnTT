#include "external/entt.hpp"
#include "config.hpp"

namespace features::player::entities
{
    entt::entity createPlayer(entt::registry &registry, Config config);
}