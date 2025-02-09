#pragma once

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"
#include "pch.hpp"

namespace features::item
{
	struct Modifier
	{
		common::entities::Stat attribute;
		common::entities::Scope scope;
		float value;
	};
	struct Item
	{
		std::string name;
		std::vector<Modifier> modifiers;
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
		{"OnAttack", Trigger::OnAttack}, {"OnShot", Trigger::OnShot}, {"OnCast", Trigger::OnCast}};

	float getTrigger(std::string trigger);
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