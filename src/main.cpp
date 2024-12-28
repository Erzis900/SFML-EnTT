#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "pch.hpp"

#include "systems/moveEntities.hpp"
#include "systems/processPhysics.hpp"
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
        if (event.type == sf::Event::Resized)
        {
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }
    }
}

void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window)
{
    features::player::systems::playerShoot(registry, window);
    features::player::systems::playerInput(registry);
    features::enemy::systems::followPlayer(registry);

    features::projectile::systems::isOnScreen(registry, window.getSize().x, window.getSize().y);
    features::projectile::systems::checkCollision(registry);

    common::systems::recalculateStat(registry);
    common::systems::applyUnitStat(registry);
    common::systems::moveEntities(registry, deltaTime);
    common::systems::processPhysics(registry, deltaTime);
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

    sf::Texture crosshairTexture;
    crosshairTexture.loadFromFile("../../assets/crosshair012.png");
    sf::Sprite crosshairSprite(crosshairTexture);
    crosshairSprite.setOrigin(crosshairTexture.getSize().x / 2.f, crosshairTexture.getSize().y / 2.f);

    auto window = sf::RenderWindow({config.screen.width, config.screen.height}, "CMake SFML Project");
    window.setFramerateLimit(config.screen.maxFps);

    int prevFpsLimit = config.screen.maxFps;
    int prevResolutionIndex = 1;
    // window.setMouseCursorVisible(false);

    tgui::Gui gui(window);
    gui.loadWidgetsFromFile("../../forms/gameForm.txt");

    auto settingsWindow = gui.get<tgui::ChildWindow>("settingsWindow");
    gui.get<tgui::Button>("settingsBtn")->onPress([&] {
        settingsWindow->setVisible(true);
        // window.setSize(sf::Vector2u(300u, 300u));    
    });

    auto fpsCheckbox = gui.get<tgui::CheckBox>("fpsCheckbox");
    auto fpsLimitCombo = gui.get<tgui::ComboBox>("fpsLimitCombo");
    auto resolutionCombo = gui.get<tgui::ComboBox>("resolutionCombo");

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
            if(fpsCheckbox->isChecked())
            {
                gui.get<tgui::Label>("fpsLabel")->setVisible(true);
                gui.get<tgui::Label>("fpsLabel")->setText("FPS: " + std::to_string(frameCount));
            }
            else 
            {
                gui.get<tgui::Label>("fpsLabel")->setVisible(false);
            }

            frameCount = 0;
            lastTime = currentTime;
        }

        processEvents(registry, window, gui);
        update(registry, deltaTime, window);

        int fpsLimit = fpsLimitCombo->getSelectedItem().toInt();
        if (fpsLimit != prevFpsLimit)
        {
            prevFpsLimit = fpsLimit;
            window.setFramerateLimit(fpsLimit);
        }

        int resolutionIndex = resolutionCombo->getSelectedItemIndex();
        if(resolutionIndex != prevResolutionIndex)
        {
            prevResolutionIndex = resolutionIndex;
            switch(resolutionIndex)
            {
                case 0:
                    window.setSize(sf::Vector2u(800u, 600u));
                    break;
                case 1:
                    window.setSize(sf::Vector2u(1280u, 720u));
                    break;
                case 2:   
                    window.setSize(sf::Vector2u(1600u, 900u));
                    break;
                case 3:   
                    window.setSize(sf::Vector2u(1920u, 1080u));
                    break;
                default:
                    break;
            }    
        }

        crosshairSprite.setPosition(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window)));

        window.clear();

        render(registry, window);
        window.draw(crosshairSprite);
        gui.draw();

        window.display();
    }
}