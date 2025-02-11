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

	void update(int fps);

  private:
	void getAttributes(entt::registry &registry);

	tgui::Gui gui;
	tgui::ChildWindow::Ptr settingsWindow;
	tgui::ChildWindow::Ptr statsWindow;
	// tgui::Button::Ptr settingsBtn;
	tgui::Picture::Ptr settingsPic;
	tgui::Picture::Ptr statsPic;

	tgui::Label::Ptr fpsLabel;

	tgui::CheckBox::Ptr fpsCheckbox;
	tgui::CheckBox::Ptr fullscreenCheckbox;

	tgui::ComboBox::Ptr fpsLimitCombo;
	tgui::ComboBox::Ptr resolutionCombo;

	tgui::Label::Ptr maxHealthLabel;
	tgui::Label::Ptr speedLabel;
	tgui::Label::Ptr damageLabel;

	tgui::Button::Ptr exitBtn;

	void handleCallbacks(sf::RenderWindow &window, StateManager &stateManager);

	sf::Vector2u windowSize;
	unsigned int fpsLimit;

	StateManager &stateManager;
};