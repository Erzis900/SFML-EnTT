#include "hud.hpp"
#include "features/ability/components/ability.hpp"
#include "features/ability/components/cooldown.hpp"

HUD::HUD(entt::registry &registry, sf::RenderWindow &window, StateManager &stateManager)
	: hud(window)
	, stateManager(stateManager)
{
	hud.loadWidgetsFromFile("../../forms/hudForm.txt");
	mainAbilityBar = hud.get<tgui::ProgressBar>("mainAbilityBar");

	mainCD = 100;
}

void HUD::handleEvent(sf::Event event) { hud.handleEvent(event); }

void HUD::draw() { hud.draw(); }

void HUD::update(entt::registry &registry)
{
	auto view = registry.view<features::ability::components::cooldown, features::ability::components::ability>();
	for (auto [entity, cooldown, ability] : view.each())
	{
		mainCD = static_cast<int>(cooldown.time * 100);
		mainAbilityBar->setValue(mainCD);
	}
}