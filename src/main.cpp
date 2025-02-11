#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "features/ability/systems/clearEvents.hpp"
#include "features/ability/systems/processAbility.hpp"
#include "features/enemy/entities/enemy.hpp"
#include "features/enemy/systems/followPlayer.hpp"
#include "features/hitbox/systems/isOnScreen.hpp"
#include "features/hitbox/systems/processHitbox.hpp"
#include "features/hitbox/systems/processInteraction.hpp"
#include "features/hitbox/systems/processLifeSpan.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/item/renderers/renderItems.hpp"
#include "features/map/map.hpp"
#include "features/player/entities/player.hpp"
#include "features/player/managers/inputManager.hpp"
#include "features/player/systems/playerCamera.hpp"
#include "features/player/systems/playerInput.hpp"
#include "gui.hpp"
#include "hud.hpp"
#include "pch.hpp"
#include "renderers/drawHealthbars.hpp"
#include "renderers/drawShapes.hpp"
#include "stateManager.hpp"
#include "systems/applyUnitStat.hpp"
#include "systems/cleanupRemoved.hpp"
#include "systems/moveEntities.hpp"
#include "systems/processDeath.hpp"
#include "systems/processPhysics.hpp"
#include "systems/recalculateStat.hpp"

void processEvents(entt::registry &registry, sf::RenderWindow &window, GUI &gui)
{
	while (const std::optional event = window.pollEvent())
	{
		gui.handleEvent(*event);
		if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		{
			window.close();
		}

		// if (const auto *resized = event->getIf<sf::Event::Resized>())
		// {
		// 	sf::FloatRect visibleArea({0, 0}, {static_cast<float>(resized->size.x), static_cast<float>(resized->size.y)});
		// 	window.setView(sf::View(visibleArea));
		// }
	}
}

void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window, features::player::InputManager &inputManager)
{
	features::player::systems::playerInput(registry, window, inputManager);
	features::player::systems::playerCamera(registry, window);

	features::enemy::systems::followPlayer(registry);

	// features::hitbox::systems::isOnScreen(registry,
	// window.getSize().x, window.getSize().y); // replaced
	// with procesLifespan
	features::hitbox::systems::processHitbox(registry);
	features::hitbox::systems::processInteraction(registry);
	features::hitbox::systems::processLifeSpan(registry, deltaTime);

	common::systems::recalculateStat(registry);
	common::systems::applyUnitStat(registry);
	common::systems::moveEntities(registry, deltaTime);
	common::systems::processPhysics(registry, deltaTime);
	features::ability::systems::processAbility(registry, deltaTime);
	common::systems::processDeath(registry);

	features::ability::systems::clearEvents(registry);	// keep in order -2
	common::systems::cleanupRemoved(registry);			// keep in order -1
}

void render(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
{
	common::renderers::drawShapes(registry, window, itemsLoader);
	features::item::renderers::renderItems(registry, window, itemsLoader);
	common::renderers::drawHealthbars(registry, window);
}

int main()
{
	Config config("../../configs/config.json");
	features::map::Map map("../../assets/map.json", "../../assets/tileset.png");
	map.setupMap();

	sf::Texture crosshairTexture;
	if (!crosshairTexture.loadFromFile("../../assets/crosshair012.png"))
	{
		std::cout << "Crosshair asset not found" << std::endl;
		return 1;
	}
	sf::Sprite crosshairSprite(crosshairTexture);
	crosshairSprite.setOrigin({crosshairTexture.getSize().x / 2.f, crosshairTexture.getSize().y / 2.f});

	auto window = sf::RenderWindow(sf::VideoMode({config.screen.width, config.screen.height}), "SFML 3.0 RPG", sf::Style::Titlebar | sf::Style::Close);
	// auto window = sf::RenderWindow(sf::VideoMode({config.screen.width, config.screen.height}), "SFML 3.0 RPG");
	window.setFramerateLimit(config.screen.maxFps);
	window.setMouseCursorVisible(false);

	StateManager stateManager;
	GUI gui(window, config, stateManager);

	entt::registry registry;

	features::item::ItemsLoader itemsLoader;
	features::player::InputManager inputManager;

	features::player::entities::createPlayer(registry, config, itemsLoader, window);
	HUD hud(registry, window, stateManager);

	for (int i = 0; i < 0; i++)
	{
		features::enemy::entities::createEnemy(registry, config, itemsLoader);
	}

	sf::Clock clock;
	sf::Clock fpsClock;
	int frameCount = 0;
	float lastTime = 0.f;
	float fpsUpdateInterval = 0.1f;

	while (window.isOpen())
	{
		float deltaTime = clock.restart().asSeconds();

		frameCount++;
		float currentTime = fpsClock.getElapsedTime().asSeconds();

		if (currentTime - lastTime >= fpsUpdateInterval)
		{
			float fps = frameCount / (currentTime - lastTime);
			frameCount = 0;
			lastTime = currentTime;

			gui.update(static_cast<int>(fps));
		}

		inputManager.processEvents(window);

		processEvents(registry, window, gui);

		if (stateManager.isActive(State::Game))
		{
			update(registry, deltaTime, window, inputManager);
			hud.update(registry);
		}

		crosshairSprite.setPosition(static_cast<sf::Vector2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

		window.clear();

		// static = drawn once
		map.drawBackground(window);

		render(registry, window, itemsLoader);

		gui.draw();
		hud.draw();

		if (stateManager.isActive(State::Game))
		{
			window.draw(crosshairSprite);
		}

		window.display();
	}
}