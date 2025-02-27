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

	tgui::ProgressBar::Ptr qAbilityBar;
	tgui::ProgressBar::Ptr eAbilityBar;
	tgui::ProgressBar::Ptr rAbilityBar;

	tgui::Picture::Ptr qSpellPic;
	tgui::Picture::Ptr eSpellPic;
	tgui::Picture::Ptr rSpellPic;

	int mainCD;

	void updateSpell(int mainCD, tgui::ProgressBar::Ptr bar, tgui::Picture::Ptr pic);
};