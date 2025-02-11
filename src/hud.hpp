#pragma once
#include "pch.hpp"
#include "stateManager.hpp"

class HUD
{
  public:
	HUD(entt::registry &registry, sf::RenderWindow &window, StateManager &stateManager);
	void handleEvent(sf::Event event);
	void draw();

	void update(entt::registry &registry);

  private:
	tgui::Gui hud;
	StateManager &stateManager;

	tgui::ProgressBar::Ptr mainAbilityBar;

	int mainCD;
};