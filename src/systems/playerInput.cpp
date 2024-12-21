#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "entt/entt.hpp"
#include "components/position.hpp"
#include "components/direction.hpp"
#include "components/playerControlled.hpp"
#include "systems/playerInput.hpp"

namespace systems
{
    void playerInput(entt::registry &registry)
    {
        auto view = registry.view<components::playerControlled>();

        sf::Vector2f dir = {0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            dir.y = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            dir.y = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            dir.x = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            dir.x = 1.f;
        }

        // Normalize the components::velocity vector
        float magnitude = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (magnitude > 0)
        {
            dir.x /= magnitude;
            dir.y /= magnitude;
        }

        for (auto [entity, playerControlled] : view.each())
        {
            std::cout << dir.x << " " << dir.y << std::endl;
            registry.replace<components::direction>(entity, dir.x, dir.y);
        }
    }
}