#include "hud.hpp"
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
	rAbilityBar = hud.get<tgui::ProgressBar>("rAbilityBar");

	qSpellPic = hud.get<tgui::Picture>("qSpellPic");
	eSpellPic = hud.get<tgui::Picture>("eSpellPic");
	rSpellPic = hud.get<tgui::Picture>("rSpellPic");
}

void HUD::handleEvent(sf::Event event) { hud.handleEvent(event); }

void HUD::draw() { hud.draw(); }

void HUD::updateSpell(int mainCD, tgui::ProgressBar::Ptr bar, tgui::Picture::Ptr pic)
{
	bar->setValue(mainCD);
	if (mainCD > 0)
	{
		pic->setInheritedOpacity(0.5);
	}
	else
	{
		pic->setInheritedOpacity(1);
	}
}

void HUD::update(entt::registry &registry)
{
	auto view = registry.view<features::ability::components::cooldown, features::ability::components::ability>();
	auto playerView = registry.view<features::player::components::playerControlled>();

	for (auto [player, playerControlled] : playerView.each())
	{
		for (auto [entity, cooldown, ability] : view.each())
		{
			if (registry.valid(ability.source) && ability.source == player)
			{
				mainCD = static_cast<int>((cooldown.time / ability.cooldownTime) * 100);

				switch (ability.slot)
				{
				case features::item::components::SlotType::Mainhand:
					updateSpell(mainCD, qAbilityBar, qSpellPic);
					break;
				case features::item::components::SlotType::Offhand:
					updateSpell(mainCD, eAbilityBar, eSpellPic);
					break;
				case features::item::components::SlotType::Cape:
					updateSpell(mainCD, rAbilityBar, rSpellPic);
					break;
				default:
					break;
				}
			}
		}
	}
}