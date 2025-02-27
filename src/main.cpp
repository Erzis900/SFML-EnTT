#define SFML_DEFINE_DISCRETE_GPU_PREFERENCE

#include "gui.hpp"
#include "hud.hpp"
#include "pch.hpp"
#include "stateManager.hpp"

#include "features/ability/systems/clearEvents.hpp"
#include "features/ability/systems/processAbility.hpp"
#include "features/animation/entities/animation.hpp"
#include "features/animation/loader/animationLoader.hpp"
#include "features/animation/systems/renderAnimation.hpp"
#include "features/effect/entities/effect.hpp"
#include "features/effect/loader/effectsLoader.hpp"
#include "features/effect/systems/processEffects.hpp"
#include "features/enemy/entities/enemy.hpp"
#include "features/enemy/systems/followPlayer.hpp"
#include "features/hitbox/systems/processHitbox.hpp"
#include "features/hitbox/systems/processInteraction.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/item/renderers/renderItems.hpp"
#include "features/map/map.hpp"
#include "features/map/systems/checkTileCollision.hpp"
#include "features/npc/entities/npc.hpp"
#include "features/npc/systems/checkInteraction.hpp"
#include "features/player/entities/player.hpp"
#include "features/player/managers/inputManager.hpp"
#include "features/player/systems/playerCamera.hpp"
#include "features/player/systems/playerInput.hpp"
#include "features/unit/loader/unitsLoader.hpp"
#include "features/unit/renderers/renderUnits.hpp"
#include "renderers/drawHealthbars.hpp"
#include "renderers/drawShapes.hpp"
#include "systems/applyUnitStat.hpp"
#include "systems/cleanupRemoved.hpp"
#include "systems/processDeath.hpp"
#include "systems/processInvalid.hpp"
#include "systems/processLifespan.hpp"
#include "systems/processPhysics.hpp"
#include "systems/processPosition.hpp"
#include "systems/processVisibility.hpp"
#include "systems/recalculateStat.hpp"
#include "systems/regenerateHealth.hpp"

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

std::unordered_map<std::string, std::vector<double>> executionTimes;

auto measureExecutionTime = [](const std::string &funcName, auto &&func, bool log, auto &&...args) {
	std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	if (log)
	{
		start = std::chrono::high_resolution_clock::now();
	}
	std::invoke(std::forward<decltype(func)>(func), std::forward<decltype(args)>(args)...);
	if (log)
	{
		end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		executionTimes[funcName].push_back(elapsed.count());

		double minTime = *std::min_element(executionTimes[funcName].begin(), executionTimes[funcName].end());
		double maxTime = *std::max_element(executionTimes[funcName].begin(), executionTimes[funcName].end());
		double avgTime = std::accumulate(executionTimes[funcName].begin(), executionTimes[funcName].end(), 0.0) / executionTimes[funcName].size();

		spdlog::debug("{:<22} Elapsed: {:.5f}s | Min: {:.5f}s | Max: {:.5f}s | Avg: {:.5f}s", funcName, elapsed.count(), minTime, maxTime, avgTime);
	}
};

static float timer = .5f;
void update(entt::registry &registry, float deltaTime, sf::RenderWindow &window, features::animation::AnimationLoader &animationLoader,
			features::player::InputManager &inputManager, sf::Vector2i mapDim, StateManager &stateManager, features::effect::EffectsLoader &effectsLoader)
{
	timer -= deltaTime;
	bool didTimerReset = false;
	if (timer <= 0.0f)
	{
		timer = 5.f;
		didTimerReset = true;
	}

	if (didTimerReset)
	{
		spdlog::debug("====================================================================================");
		spdlog::debug("Measure systems execution times gathered every {}s", static_cast<int>(timer));
		spdlog::debug("====================================================================================");
	}
	std::tuple<std::string, std::function<void()>> systems[] = {
		{"playerInput", [&] { features::player::systems::playerInput(registry, window, inputManager); }},
		{"followPlayer", [&] { features::enemy::systems::followPlayer(registry); }},
		{"checkInteraction", [&] { features::npc::systems::checkInteraction(registry, window, inputManager); }},
		{"processAbility", [&] { features::ability::systems::processAbility(registry, deltaTime); }},
		{"processHitbox", [&] { features::hitbox::systems::processHitbox(registry); }},
		{"processInteraction", [&] { features::hitbox::systems::processInteraction(registry, effectsLoader); }},
		{"processLifespan", [&] { common::systems::processLifespan(registry, deltaTime); }},
		{"processEffects", [&] { features::effect::systems::processEffects(registry, deltaTime, effectsLoader); }},
		{"recalculateStat", [&] { common::systems::recalculateStat(registry); }},							// keep -11
		{"applyUnitStat", [&] { common::systems::applyUnitStat(registry); }},								// keep -10
		{"regenerateHealth", [&] { common::systems::regenerateHealth(registry, deltaTime); }},				// keep -9
		{"processPosition", [&] { common::systems::processPosition(registry, deltaTime); }},				// keep -9
		{"processPhysics", [&] { common::systems::processPhysics(registry, deltaTime, mapDim, window); }},	// keep -8
		{"checkTileCollision", [&] { features::map::systems::checkTileCollision(registry, deltaTime); }},	// keep -7
		{"playerCamera", [&] { features::player::systems::playerCamera(registry, window); }},				// keep -6
		{"processVisibility", [&] { common::systems::processVisibility(registry, window); }},				// keep -5
		{"processDeath", [&] { common::systems::processDeath(registry, stateManager); }},					// keep -4
		{"clearEvents", [&] { features::ability::systems::clearEvents(registry); }},						// keep -3
		{"processInvalid", [&] { common::systems::processInvalid(registry); }},								// keep -2
		{"cleanupRemoved", [&] { common::systems::cleanupRemoved(registry); }},								// keep -1
	};

	for (const auto &[name, func] : systems)
	{
		measureExecutionTime(name, func, didTimerReset);
	}
	if (didTimerReset)
	{
		spdlog::debug("====================================================================================");
	}
}

static float renderTimer = .5f;
void render(entt::registry &registry, float deltaTime, sf::RenderWindow &window, features::unit::UnitsLoader &unitsLoader,
			features::item::ItemsLoader &itemsLoader, features::animation::AnimationLoader &animationLoader)
{
	renderTimer -= deltaTime;
	bool didTimerReset = false;
	if (renderTimer <= 0.0f)
	{
		renderTimer = 5.f;
		didTimerReset = true;
	}

	if (didTimerReset)
	{
		spdlog::debug("====================================================================================");
		spdlog::debug("Measure renderers draw times gathered every {}s", static_cast<int>(renderTimer));
		spdlog::debug("====================================================================================");
	}
	std::tuple<std::string, std::function<void()>> renderers[] = {
		{"drawShapes", [&] { common::renderers::drawShapes(registry, window, itemsLoader); }},
		{"renderUnits", [&] { features::unit::renderers::renderUnits(registry, window, unitsLoader); }},
		{"renderItems", [&] { features::item::renderers::renderItems(registry, window, itemsLoader); }},
		{"renderAnimations", [&] { features::animation::renderers::renderAnimations(registry, window, animationLoader); }},
		{"drawHealthbars", [&] { common::renderers::drawHealthbars(registry, window); }},
	};

	for (const auto &[name, func] : renderers)
	{
		measureExecutionTime(name, func, didTimerReset);
	}
	if (didTimerReset)
	{
		spdlog::debug("====================================================================================");
	}
}

int main()
{
	spdlog::set_level(spdlog::level::debug);
	spdlog::info("Start");

	Config config("../../configs/config.json");

	features::map::Map map("../../public/map.json", "../../public/tileset.png");

	sf::Texture crosshairTexture;
	std::string crosshairPath = "../../public/crosshair.png";
	if (!crosshairTexture.loadFromFile(crosshairPath))
	{
		spdlog::error("Failed to load {}", crosshairPath);
		return EXIT_FAILURE;
	}
	spdlog::info("Loaded {}", crosshairPath);

	sf::Sprite crosshairSprite(crosshairTexture);
	// crosshairSprite.setOrigin({crosshairTexture.getSize().x / 2.f, crosshairTexture.getSize().y / 2.f});

	auto window = sf::RenderWindow(sf::VideoMode({config.screen.width, config.screen.height}), "SFML 3.0 RPG", sf::Style::Titlebar | sf::Style::Close);
	// auto window = sf::RenderWindow(sf::VideoMode({config.screen.width, config.screen.height}), "SFML 3.0 RPG");
	window.setFramerateLimit(config.screen.maxFps);
	window.setMouseCursorVisible(false);
	spdlog::info("Window created");

	StateManager stateManager;

	entt::registry registry;
	spdlog::info("Registry created");
	map.setupMap(registry);

	features::item::ItemsLoader itemsLoader;
	features::unit::UnitsLoader unitsLoader;
	features::effect::EffectsLoader effectsLoader;
	features::player::InputManager inputManager;

	entt::entity player = features::player::entities::createPlayer(registry, itemsLoader, unitsLoader);
	spdlog::debug("Player entity created, ID {}", static_cast<int>(player));

	GUI gui(window, config, registry, stateManager);
	HUD hud(registry, window, stateManager);

	features::animation::AnimationLoader animationLoader;

	for (int i = 0; i < 0; i++)
	{
		entt::entity enemy = features::enemy::entities::createEnemy(registry, itemsLoader, unitsLoader);
		spdlog::debug("Enemy entity created, ID {}", static_cast<int>(enemy));
	}

	sf::SoundBuffer buffer("../../public/audio/hello.wav");
	sf::Sound sound(buffer);
	features::npc::entities::createNPC(registry, sound);

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

			gui.update(registry, static_cast<int>(fps));
		}

		processEvents(registry, window, gui);
		inputManager.processEvents(window);

		if (stateManager.isActive(State::Game))
		{
			update(registry, deltaTime, window, animationLoader, inputManager, map.getMapDim(), stateManager, effectsLoader);
			hud.update(registry);
		}
		else if (stateManager.isActive(State::GameOver))
		{
			spdlog::info("Reached game over state");

			// for now we'll go back to game state
			stateManager.setState(State::GameOver, false);
			stateManager.setState(State::Game, true);
		}

		crosshairSprite.setPosition(static_cast<sf::Vector2f>(window.mapPixelToCoords(sf::Mouse::getPosition(window))));

		window.clear();

		// static = drawn once
		map.drawBackground(window);

		render(registry, deltaTime, window, unitsLoader, itemsLoader, animationLoader);

		gui.draw();
		hud.draw();

		window.draw(crosshairSprite);

		window.display();
	}
}