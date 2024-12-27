#include <SFML/Graphics.hpp>

#include "external/entt.hpp"

#include "components/position.hpp"

namespace common::renderers
{
    void drawShapes(entt::registry &registry, sf::RenderWindow &window);
}