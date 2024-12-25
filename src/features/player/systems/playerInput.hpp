#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "external/entt.hpp"
#include "components/direction.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::player::systems
{
    void playerInput(entt::registry &registry);
}
