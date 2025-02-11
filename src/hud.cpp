#include "hud.hpp"
#include "components/maxHealth.hpp"
#include "features/ability/components/ability.hpp"
#include "features/ability/components/cooldown.hpp"
#include "features/item/components/equipped.hpp"
#include "features/player/components/playerControlled.hpp"

HUD::HUD(entt::registry &registry, sf::RenderWindow &window, StateManager &stateManager)
	: hud(window)
	, stateManager(stateManager)
{
	hud.loadWidgetsFromFile("../../forms/hudForm.txt");
	qAbilityBar = hud.get<tgui::ProgressBar>("qAbilityBar");
	eAbilityBar = hud.get<tgui::ProgressBar>("eAbilityBar");
	qSpellPic = hud.get<tgui::Picture>("qSpellPic");
	eSpellPic = hud.get<tgui::Picture>("eSpellPic");

	getAttributes(registry);
}

void HUD::handleEvent(sf::Event event) { hud.handleEvent(event); }

void HUD::draw() { hud.draw(); }

void HUD::update(entt::registry &registry)
{
	auto view = registry.view<features::ability::components::cooldown, features::ability::components::ability>();
	for (auto [entity, cooldown, ability] : view.each())
	{
		mainCD = static_cast<int>(cooldown.time * 100);

		if (ability.slot == features::item::components::SlotType::Mainhand)
		{
			qAbilityBar->setValue(mainCD);
			if (mainCD > 0)
			{
				qSpellPic->setInheritedOpacity(0.5);
			}
			else
			{
				qSpellPic->setInheritedOpacity(1);
			}
		}
		else if (ability.slot == features::item::components::SlotType::Offhand)
		{
			eAbilityBar->setValue(mainCD);
			if (mainCD > 0)
			{
				eSpellPic->setInheritedOpacity(0.5);
			}
			else
			{
				eSpellPic->setInheritedOpacity(1);
			}
		}
	}
}

void HUD::getAttributes(entt::registry &registry)
{
	auto view = registry.view<features::player::components::playerControlled, common::components::maxHealth>();
	for (auto [entity, playerControlled, maxHealth] : view.each())
	{
		std::cout << maxHealth.value << std::endl;
	}
}
