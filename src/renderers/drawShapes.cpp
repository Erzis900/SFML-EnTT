#include <SFML/Graphics.hpp>

#include "external/entt.hpp"

#include "components/position.hpp"
#include "components/renderable.hpp"

namespace common::renderers
{
    void drawShapes(entt::registry &registry, sf::RenderWindow &window)
    {
        auto view = registry.view<common::components::position, common::components::renderable>();

        for (auto [entity, pos, render] : view.each())
        {
            render.shape.setPosition({pos.x, pos.y});
            window.draw(render.shape);
        }
    }
}