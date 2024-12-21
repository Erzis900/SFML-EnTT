#include <SFML/Graphics.hpp>
#include "entt/entt.hpp"
#include <random>
#include <iostream>

#include "components/position.hpp"
#include "components/direction.hpp"
#include "components/speed.hpp"

#include "systems/moveEntities.hpp"

#include "features/player/components/playerControlled.hpp"
#include "features/player/systems/playerInput.hpp"
#include "features/player/systems/playerShoot.hpp"
#include "features/player/entities/player.hpp"

#include "entities/projectile.hpp"

sf::CircleShape CreateO(common::components::position pos)
{
    // Radius: 50px
    sf::CircleShape o(50);
    o.setFillColor(sf::Color::White);
    o.setOutlineThickness(1);
    o.setOutlineColor(sf::Color::White);
    o.setPosition(pos.x, pos.y);
    return o;
}

void processEvents(entt::registry &registry, sf::RenderWindow &window)
{
    for (auto event = sf::Event(); window.pollEvent(event);)
    {
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
        features::player::systems::playerShoot(registry, window);
    }
}

void update(entt::registry &registry, float deltaTime)
{
    features::player::systems::playerInput(registry);
    common::systems::moveEntities(registry, deltaTime);
}

void render(entt::registry &registry, sf::RenderWindow &window)
{
    window.clear();

    const auto &cregistry = registry;
    auto view = registry.view<common::components::position>();

    for (auto entity : view)
    {
        auto [pos] = view.get(entity);
        window.draw(CreateO(pos));
    }

    window.display();
}

int main()
{
    auto window = sf::RenderWindow({1280u, 720u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    entt::registry registry;
    features::player::entities::createPlayer(registry);

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents(registry, window);
        update(registry, deltaTime);
        render(registry, window);
    }
}
