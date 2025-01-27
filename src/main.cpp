#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "pch.hpp"

#include "systems/moveEntities.hpp"
#include "systems/processPhysics.hpp"
#include "systems/processCooldown.hpp"
#include "systems/recalculateStat.hpp"
#include "systems/applyUnitStat.hpp"
#include "systems/cleanupRemoved.hpp"
#include "systems/processDeath.hpp"

#include "renderers/drawShapes.hpp"
#include "renderers/drawHealthbars.hpp"

#include "features/enemy/entities/enemy.hpp"
#include "features/enemy/systems/followPlayer.hpp"

#include "features/player/entities/player.hpp"
#include "features/player/systems/playerInput.hpp"
#include "features/player/systems/playerShoot.hpp"

#include "features/hitbox/systems/processHitbox.hpp"
#include "features/hitbox/systems/isOnScreen.hpp"
#include "features/hitbox/systems/processLifeSpan.hpp"
#include "features/hitbox/systems/processInteraction.hpp"

void processEvents(entt::registry &registry, sf::RenderWindow &window, tgui::Gui &gui)
{
    while (const std::optional event = window.pollEvent())
    {
        gui.handleEvent(*event);
        if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
        {
            window.close();
        }

        if (event->is<sf::Event::Resized>())
        {
            // sf::FloatRect visibleArea({0, 0}, {event.size.width, event.size.height});
            // window.setView(sf::View(visibleArea));
        }
    }
}

void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window)
{
    features::player::systems::playerShoot(registry, window);
    features::player::systems::playerInput(registry);
    features::enemy::systems::followPlayer(registry);

    // features::hitbox::systems::isOnScreen(registry, window.getSize().x, window.getSize().y); // replaced with procesLifespan
    features::hitbox::systems::processHitbox(registry);
    features::hitbox::systems::processInteraction(registry);
    features::hitbox::systems::processLifeSpan(registry, deltaTime);

    common::systems::recalculateStat(registry);
    common::systems::applyUnitStat(registry);
    common::systems::moveEntities(registry, deltaTime);
    common::systems::processPhysics(registry, deltaTime);
    common::systems::processCooldown(registry, deltaTime);
    common::systems::processDeath(registry);

    common::systems::cleanupRemoved(registry); // keep last
}

void render(entt::registry &registry, sf::RenderWindow &window)
{
    common::renderers::drawShapes(registry, window);
    common::renderers::drawHealthbars(registry, window);
}

int main()
{
    Config config("../../configs/config.json");

    sf::Texture crosshairTexture;
    if(!crosshairTexture.loadFromFile("../../assets/crosshair012.png"))
    {
        std::cout << "Crosshair asset not found" << std::endl;
        return 0;
    }
    sf::Sprite crosshairSprite(crosshairTexture);
    crosshairSprite.setOrigin({crosshairTexture.getSize().x / 2.f, crosshairTexture.getSize().y / 2.f});

    auto window = sf::RenderWindow(sf::VideoMode({config.screen.width, config.screen.height}), "SFML 3.0 RPG");
    window.setFramerateLimit(config.screen.maxFps);
    // window.setMouseCursorVisible(false);

    tgui::Gui gui(window);
    gui.loadWidgetsFromFile("../../forms/gameForm.txt");

    auto settingsWindow = gui.get<tgui::ChildWindow>("settingsWindow");
    gui.get<tgui::Button>("settingsBtn")->onPress([&] {
        settingsWindow->setVisible(true);
        // window.setSize(sf::Vector2u(300u, 300u));    
    });

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

    while (window.isOpen())
    {
        float deltaTime = clock.restart().asSeconds();

        frameCount++;
        float currentTime = fpsClock.getElapsedTime().asSeconds();

        if (currentTime - lastTime >= 1.0f)
        {
            frameCount = 0;
            lastTime = currentTime;
        }

        processEvents(registry, window, gui);
        update(registry, deltaTime, window);

        crosshairSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.clear();

        render(registry, window);
        window.draw(crosshairSprite);
        gui.draw();

        window.display();
    }
}