#include <SFML/Graphics.hpp>
#include "../inc/entt.hpp"
#include <random>
#include <iostream>
#include "components/position.hpp"
#include "components/velocity.hpp"
#include "systems/playerInput.hpp"

sf::CircleShape CreateO(components::position pos)
{
    // Radius: 50px
    sf::CircleShape o(50);
    o.setFillColor(sf::Color::White);
    o.setOutlineThickness(1);
    o.setOutlineColor(sf::Color::White);
    o.setPosition(pos.x, pos.y);
    return o;
}

int main()
{
    auto window = sf::RenderWindow({1920u, 1080u}, "CMake SFML Project");
    window.setFramerateLimit(144);
    entt::registry registry;

    for (auto i = 0u; i < 3u; ++i)
    {
        const auto entity = registry.create();
        registry.emplace<components::position>(entity, i * 30.f, i * 150.f);
        registry.emplace<components::velocity>(entity, 2.f, 2.f);
    }

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                window.close();
            }
        }

        window.clear();
        systems::playerInput(registry);

        const auto &cregistry = registry;
        auto view = registry.view<components::position, components::velocity>();

        for (auto entity : view)
        {
            auto [pos, vel] = view.get(entity);
            window.draw(CreateO(pos));
        }
        window.display();
    }
}
