#pragma once
#include "config.hpp"
#include "pch.hpp"
#include "stateManager.hpp"

class GUI
{
  public:
	GUI(sf::RenderWindow &window, Config &config, entt::registry &registry, StateManager &stateManager);
	void handleEvent(sf::Event event);
	void draw();

	void update(entt::registry &registry, int fps);

  private:
	void getAttributes(entt::registry &registry);

	tgui::Gui gui;
	tgui::ChildWindow::Ptr settingsWindow;
	tgui::ChildWindow::Ptr statsWindow;
	tgui::ChildWindow::Ptr inventoryWindow;

	tgui::Picture::Ptr settingsPic;
	tgui::Picture::Ptr statsPic;
	tgui::Picture::Ptr inventoryPic;

	tgui::Label::Ptr fpsLabel;

	// settings
	tgui::CheckBox::Ptr fpsCheckbox;
	tgui::CheckBox::Ptr fullscreenCheckbox;

	tgui::ComboBox::Ptr fpsLimitCombo;
	tgui::ComboBox::Ptr resolutionCombo;

	tgui::Label::Ptr maxHealthLabel;
	tgui::Button::Ptr exitBtn;

	// character page
	tgui::Label::Ptr speedLabel;
	tgui::Label::Ptr damageLabel;

	void handleCallbacks(sf::RenderWindow &window, StateManager &stateManager);

	sf::Vector2u windowSize;
	unsigned int fpsLimit;

	StateManager &stateManager;
};