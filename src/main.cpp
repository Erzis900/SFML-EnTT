#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "pch.hpp"

#include "systems/moveEntities.hpp"
#include "systems/processCooldown.hpp"
#include "systems/recalculateStat.hpp"
#include "systems/applyUnitStat.hpp"

#include "renderers/drawShapes.hpp"
#include "renderers/drawHealthbars.hpp"

#include "features/enemy/entities/enemy.hpp"
#include "features/enemy/systems/followPlayer.hpp"

#include "features/player/entities/player.hpp"
#include "features/player/systems/playerInput.hpp"
#include "features/player/systems/playerShoot.hpp"

#include "features/projectile/entities/projectile.hpp"
#include "features/projectile/systems/checkCollision.hpp"
#include "features/projectile/systems/isOnScreen.hpp"

void processEvents(entt::registry &registry, sf::RenderWindow &window, tgui::Gui &gui)
{
    for (auto event = sf::Event(); window.pollEvent(event);)
    {
        gui.handleEvent(event);
        if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            window.close();
        }
    }
}

void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window, Config config)
{
    features::player::systems::playerShoot(registry, window);
    features::player::systems::playerInput(registry);
    features::enemy::systems::followPlayer(registry);

    features::projectile::systems::isOnScreen(registry, window.getSize().x, window.getSize().y);
    features::projectile::systems::checkCollision(registry, config.projectile.radius, config.enemy.radius);

    common::systems::recalculateStat(registry);
    common::systems::applyUnitStat(registry);
    common::systems::moveEntities(registry, deltaTime);
    common::systems::processCooldown(registry, deltaTime);
}

void render(entt::registry &registry, sf::RenderWindow &window)
{
    common::renderers::drawShapes(registry, window);
    common::renderers::drawHealthbars(registry, window);
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

    auto window = sf::RenderWindow({config.screen.width, config.screen.height}, "CMake SFML Project");
    window.setFramerateLimit(config.screen.maxFps);

    tgui::Gui gui(window);

    entt::registry registry;
    features::player::entities::createPlayer(registry, config);

    for (int i = 0; i < 20; i++)
    {
        features::enemy::entities::createEnemy(registry, config);
    }

    sf::Clock clock;
    sf::Clock fpsClock;
    int frameCount = 0;
    float lastTime = 0.f;

    tgui::Label::Ptr label = tgui::Label::create();
    label->setText("Hello world.\nLorem ipsum dolor sit amet");

    // An auto-sizing label can be given a maximum width where text should start at a new line
    label->setMaximumTextWidth(300);

    // If setSize is called then the size no longer depends on the text inside the label
    // and a vertical scrollbar can appear if the text does not fit.
    label->setSize({300, 400});
    tgui::HorizontalAlignment(tgui::HorizontalAlignment::Right);
    label->setPosition(10, 10);
    gui.add(label);

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        frameCount++;
        float currentTime = fpsClock.getElapsedTime().asSeconds();

        if (currentTime - lastTime >= 1.0f)
        {
            fpsText.setString("FPS: " + std::to_string(frameCount));

            frameCount = 0;
            lastTime = currentTime;
        }

        processEvents(registry, window, gui);
        update(registry, deltaTime, window, config);

        window.clear();
        render(registry, window);
        window.draw(fpsText);
        gui.draw();
        window.display();
    }
}
