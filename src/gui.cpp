#include "gui.hpp"
#include "components/damage.hpp"
#include "components/maxHealth.hpp"
#include "components/speed.hpp"
#include "features/ability/components/cooldown.hpp"
#include "features/player/components/playerControlled.hpp"
#include "features/player/systems/playerCamera.hpp"

GUI::GUI(sf::RenderWindow &window, Config &config, entt::registry &registry, StateManager &stateManager)
	: gui(window)
	, stateManager(stateManager)
{
	gui.loadWidgetsFromFile("../../forms/gameForm.txt");

	settingsWindow = gui.get<tgui::ChildWindow>("settingsWindow");
	statsWindow = gui.get<tgui::ChildWindow>("statsWindow");
	inventoryWindow = gui.get<tgui::ChildWindow>("inventoryWindow");

	// settings
	settingsPic = gui.get<tgui::Picture>("settingsPic");
	fpsCheckbox = gui.get<tgui::CheckBox>("fpsCheckbox");
	fpsLimitCombo = gui.get<tgui::ComboBox>("fpsLimitCombo");
	resolutionCombo = gui.get<tgui::ComboBox>("resolutionCombo");
	fpsLabel = gui.get<tgui::Label>("fpsLabel");
	fullscreenCheckbox = gui.get<tgui::CheckBox>("fullscreenCheckbox");
	maxHealthLabel = gui.get<tgui::Label>("maxHealthLabel");
	exitBtn = gui.get<tgui::Button>("exitBtn");

	// character page
	statsPic = gui.get<tgui::Picture>("statsPic");
	speedLabel = gui.get<tgui::Label>("speedLabel");
	damageLabel = gui.get<tgui::Label>("damageLabel");

	// inventory
	inventoryPic = gui.get<tgui::Picture>("inventoryPic");

	fpsLabel->setVisible(fpsCheckbox->isChecked());

	fpsLimit = config.screen.maxFps;
	windowSize = {config.screen.width, config.screen.height};

	handleCallbacks(window, stateManager);
}

void GUI::handleEvent(sf::Event event) { gui.handleEvent(event); }

void GUI::draw() { gui.draw(); }

void GUI::update(entt::registry &registry, int fps)
{
	if (fpsCheckbox->isChecked())
	{
		fpsLabel->setText("FPS: " + std::to_string(static_cast<int>(fps)));
	}
	getAttributes(registry);
}

void GUI::handleCallbacks(sf::RenderWindow &window, StateManager &stateManager)
{
	settingsPic->onMousePress([this, &window, &stateManager] {
		settingsWindow->setVisible(!settingsWindow->isVisible());

		// window.setMouseCursorVisible(settingsWindow->isVisible());

		stateManager.setState(State::Settings, !stateManager.isActive(State::Settings));

		stateManager.setState(State::Game, !stateManager.isActive(State::Game));
	});

	statsPic->onMousePress([this, &window] { statsWindow->setVisible(!statsWindow->isVisible()); });
	inventoryPic->onMousePress([this, &window] { inventoryWindow->setVisible(!inventoryWindow->isVisible()); });

	settingsPic->onMouseEnter([this] { settingsPic->setInheritedOpacity(0.5); });
	settingsPic->onMouseLeave([this] { settingsPic->setInheritedOpacity(1); });

	statsPic->onMouseEnter([this] { statsPic->setInheritedOpacity(0.5); });
	statsPic->onMouseLeave([this] { statsPic->setInheritedOpacity(1); });

	inventoryPic->onMouseEnter([this] { inventoryPic->setInheritedOpacity(0.5); });
	inventoryPic->onMouseLeave([this] { inventoryPic->setInheritedOpacity(1); });

	// settingsBtn->onPress([this, &window, &stateManager] {
	// 	settingsWindow->setVisible(!settingsWindow->isVisible());

	// 	window.setMouseCursorVisible(settingsWindow->isVisible());

	// 	stateManager.setState(State::Settings, !stateManager.isActive(State::Settings));

	// 	stateManager.setState(State::Game, !stateManager.isActive(State::Game));
	// });

	settingsWindow->onClose([this, &window, &stateManager] {
		// window.setMouseCursorVisible(false);

		stateManager.setState(State::Settings, false);
		stateManager.setState(State::Game, true);
	});

	fpsCheckbox->onChange([this] { fpsLabel->setVisible(fpsCheckbox->isChecked()); });

	fpsLimitCombo->onItemSelect([this, &window] {
		fpsLimit = fpsLimitCombo->getSelectedItem().toInt();
		window.setFramerateLimit(fpsLimit);
	});

	resolutionCombo->onItemSelect([this, &window] {
		std::stringstream ss(resolutionCombo->getSelectedItem().toStdString());

		std::vector<std::string> tokens;
		std::string token;
		while (std::getline(ss, token, 'x'))
		{
			tokens.push_back(token);
		}

		windowSize = {static_cast<unsigned int>(std::stoi(tokens[0])), static_cast<unsigned int>(std::stoi(tokens[1]))};

		window.setSize(windowSize);

		// TODO fix gui viewport
		gui.setAbsoluteView({0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
	});

	fullscreenCheckbox->onChange([this, &window] {
		if (fullscreenCheckbox->isChecked())
		{
			sf::View view = window.getView();
			window.create(sf::VideoMode::getFullscreenModes()[0], "SFML 3.0 RPG", sf::State::Fullscreen);
			window.setView(getLetterboxView(view, window.getSize().x, window.getSize().y));
			window.setFramerateLimit(fpsLimit);
		}
		else
		{
			window.create(sf::VideoMode(windowSize), "SFML 3.0 RPG");

			window.setFramerateLimit(fpsLimit);
		}

		// TODO fix gui viewport
		gui.setAbsoluteView({0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)});
	});

	exitBtn->onClick([this, &window] { window.close(); });
}

void GUI::getAttributes(entt::registry &registry)
{
	auto view = registry.view<features::player::components::playerControlled, common::components::maxHealth, common::components::speed>();
	for (auto [entity, maxHealth, speed] : view.each())
	{
		maxHealthLabel->setText("Max Health: " + std::to_string(maxHealth.value));
		speedLabel->setText("Speed: " + std::to_string(speed.value));
		// damageLabel->setText("Damage: " + std::to_string(damage.value));
	}
}