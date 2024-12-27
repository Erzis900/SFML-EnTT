#include "drawShapes.hpp"
#include "components/position.hpp"
#include "components/shape.hpp"

namespace common::renderers
{
    void drawShapes(entt::registry &registry, sf::RenderWindow &window)
    {
        auto view = registry.view<common::components::position, common::components::shape>();

        for (auto [entity, pos, shape] : view.each())
        {
            shape.value.setPosition({pos.x, pos.y});
            window.draw(shape.value);
        }
    }
}