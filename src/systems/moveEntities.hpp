#ifndef MOVESYSTEM_HPP
#define MOVESYSTEM_HPP

#include "entt/entt.hpp"

namespace systems
{
    void moveEntities(entt::registry &registry, float deltaTime);
}

#endif // MOVESYSTEM_HPP
