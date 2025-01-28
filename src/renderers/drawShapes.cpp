#include "drawShapes.hpp"

namespace common::renderers {
    void drawShapes(entt::registry& registry, sf::RenderWindow& window, features::item::ItemsLoader& itemsLoader) {
        auto view = registry.view<
            common::components::position,
            common::components::renderable,
            common::components::direction
        >();

        for (auto [entity, pos, render, dir] : view.each()) {
            render.shape.setPosition({ pos.x, pos.y });
            window.draw(render.shape);

            sf::Sprite sprite = itemsLoader.getSprite(4);
            sprite.setPosition({ pos.x, pos.y });
            sprite.setRotation(
                sf::degrees(std::atan2(dir.y, dir.x) * 180 / M_PI) -
                sf::degrees(dir.y == 0 && dir.x == 0 ? 0 : 90)
            );
            window.draw(sprite);
        }
    }
}
