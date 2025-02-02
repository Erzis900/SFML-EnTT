#pragma once

#include "components/modifiers.hpp"
#include "entities/attribute.hpp"
#include "pch.hpp"

namespace features::item
{
	struct Modifier
	{
		common::entities::Stat attribute;
		float value;
		common::entities::Scope scope;
	};
	struct Item
	{
		int id;
		std::string name;
		int x;
		int y;
		int width;
		int height;
		std::vector<Modifier> modifiers;
	};
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