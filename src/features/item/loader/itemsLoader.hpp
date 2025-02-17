#pragma once

#include "pch.hpp"

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"

#include "../components/equipped.hpp"

namespace features::item
{
	struct Modifier
	{
		common::entities::Stat attribute;
		common::entities::Scope scope;
		float value;
	};

	enum Type : int
	{
		NoItem = 0,
		Sword = 1,
		Club,
		Quiver,
		Shield,
		Scepter,
		Shoulder,
		Head,
		Cape,
		Bow
	};

	struct Item
	{
		std::string name;
		std::vector<Modifier> modifiers;
		components::SlotType slot;
		Type type;
		int id;
		int x;
		int y;
		int width;
		int height;
	};
	enum Trigger : int
	{
		OnNone = 0,
		OnAttack = 1,
		OnShot = 2,
		OnCast = 3
	};
	static std::unordered_map<std::string, Trigger> const mapTrigger = {
		{"on-attack", Trigger::OnAttack}, {"on-shot", Trigger::OnShot}, {"on-cast", Trigger::OnCast}};

	float getTrigger(std::string trigger);

	static std::unordered_map<std::string, Type> const mapType = {{"sword", Type::Sword},	{"club", Type::Club},		{"quiver", Type::Quiver},
																  {"shield", Type::Shield}, {"scepter", Type::Scepter}, {"shoulder", Type::Shoulder},
																  {"head", Type::Head},		{"cape", Type::Cape},		{"bow", Type::Bow}};

	static std::unordered_map<std::string, components::SlotType> const mapSlot = {
		{"head", components::SlotType::Head},
		{"chest", components::SlotType::Chest},
		{"main-shoulder", components::SlotType::MainShoulder},
		{"off-shoulder", components::SlotType::OffShoulder},
		{"mainhand", components::SlotType::Mainhand},
		{"offhand", components::SlotType::Offhand},
		{"cape", components::SlotType::Cape},
	};

	Type getType(std::string type);
	components::SlotType getSlot(std::string slot);
	class ItemsLoader
	{
	  public:
		ItemsLoader();
		Item getItem(int id);
		sf::Sprite getSprite(int id);

	  private:
		std::map<int, Item> itemsData = {};
		sf::Texture texture;
	};

}  // namespace features::item