#include "playerInput.hpp"
#include "components/direction.hpp"
#include "features/player/components/playerControlled.hpp"

namespace features::player::systems {
    void playerInput(entt::registry &registry)
    {
        auto view = registry.view<features::player::components::playerControlled>();

        sf::Vector2f dir = {0.f, 0.f};

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            dir.y = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            dir.y = 1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            dir.x = -1.f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
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
            // std::cout << dir.x << " " << dir.y << std::endl;
            registry.replace<common::components::direction>(entity, dir.x, dir.y);
        }
    }
}  // namespace features::player::systems