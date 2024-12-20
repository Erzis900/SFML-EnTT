#include <SFML/Graphics.hpp>
#include <random>
#include <iostream>
#include "inc/entt.hpp"
#include "components/position.hpp"
#include "components/velocity.hpp"
#include "playerInput.hpp"

namespace systems
{
    void handlePlayerInput(entt::registry &registry)
    {
        auto view = registry.view<components::position, components::velocity>();

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

        for (auto [entity, pos, vel] : view.each())
        {
            std::cout << dir.x << " " << dir.y << std::endl;
            registry.replace<components::position>(entity, pos.x + vel.dx * dir.x, pos.y + vel.dy * dir.y);

            if (-20 > pos.x || pos.x > 1200)
            {
                registry.replace<components::velocity>(entity, -vel.dx, vel.dy);
            }
            if (-20 > pos.y || pos.y > 800)
            {
                registry.replace<components::velocity>(entity, vel.dx, -vel.dy);
            }
        }
    }
}