#include <SFML/Graphics.hpp>
#include "external/entt.hpp"
#include <random>
#include <iostream>

#include "components/position.hpp"
#include "components/direction.hpp"
#include "components/speed.hpp"
#include "components/shape.hpp"

#include "systems/moveEntities.hpp"
#include "systems/processCooldown.hpp"
#include "features/enemy/systems/followPlayer.hpp"

#include "features/player/components/playerControlled.hpp"
#include "features/player/systems/playerInput.hpp"
#include "features/player/systems/playerShoot.hpp"
#include "features/player/entities/player.hpp"

#include "features/enemy/entities/enemy.hpp"

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
    features::enemy::systems::followPlayer(registry);

    common::systems::moveEntities(registry, deltaTime);
    common::systems::processCooldown(registry, deltaTime);
}

void render(entt::registry &registry, sf::RenderWindow &window)
{
    window.clear();

    const auto &cregistry = registry;
    // auto view = registry.view<common::components::position, features::player::components::shape>();
    auto view = registry.view<common::components::position, common::components::shape>();

    for (auto entity : view)
    {
        auto [pos, shape] = view.get(entity);
        shape.value.setPosition({pos.x, pos.y});
        window.draw(shape.value);
    }

    window.display();
}

int main()
{
    auto window = sf::RenderWindow({1280u, 720u}, "CMake SFML Project");
    window.setFramerateLimit(144);

    entt::registry registry;
    features::player::entities::createPlayer(registry);
    features::enemy::entities::createEnemy(registry);

    sf::Clock clock;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        processEvents(registry, window);
        update(registry, deltaTime);
        render(registry, window);
    }
}
