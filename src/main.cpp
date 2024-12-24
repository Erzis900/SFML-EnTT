#include <SFML/Graphics.hpp>
#include "external/entt.hpp"
#include <random>
#include <iostream>

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

#include "features/projectile/entities/projectile.hpp"
#include "features/projectile/systems/checkCollision.hpp"
#include "features/projectile/systems/isOnScreen.hpp"

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
    }
}

void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window)
{
    
    features::player::systems::playerShoot(registry, window);
    features::player::systems::playerInput(registry);
    features::enemy::systems::followPlayer(registry);

    features::projectile::systems::checkCollision(registry);
    features::projectile::systems::isOnScreen(registry, window.getSize().x, window.getSize().y);

    common::systems::moveEntities(registry, deltaTime);
    common::systems::processCooldown(registry, deltaTime);
}

void render(entt::registry &registry, sf::RenderWindow &window, sf::Text &text)
{
    window.clear();

    window.draw(text);

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
    Config config("../../configs/config.json");

    sf::Font font;
    font.loadFromFile("../../fonts/Arial.ttf");

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(24);
    fpsText.setFillColor(sf::Color::White);

    auto window = sf::RenderWindow({config.screenWidth, config.screenHeight}, "CMake SFML Project");
    window.setFramerateLimit(config.maxFps);

    entt::registry registry;
    features::player::entities::createPlayer(registry, config);

    for (int i = 0; i < 5; i++)
    {
        features::enemy::entities::createEnemy(registry);
    }

    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;
    float lastTime = 0.f;

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        frameCount++;
        float currentTime = fpsClock.getElapsedTime().asSeconds();

        if (currentTime - lastTime >= 1.0f) {
            fpsText.setString("FPS: " + std::to_string(frameCount));

            frameCount = 0;
            lastTime = currentTime;
        }

        processEvents(registry, window);
        update(registry, deltaTime, window);
        render(registry, window, fpsText);
    }
}
