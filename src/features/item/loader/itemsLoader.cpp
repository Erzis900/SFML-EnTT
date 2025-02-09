#include "itemsLoader.hpp"

namespace features::item
{
	ItemsLoader::ItemsLoader()
	{
		std::ifstream itemsFile("../../data/items.json");
		nlohmann::json data = nlohmann::json::parse(itemsFile);
		texture = sf::Texture("../../assets/items.png", false, sf::IntRect({0, 0}, {512, 512}));

		for (auto &itemJson : data)
		{
			std::vector<Modifier> modifiers = {};
			for (auto &modifierJson : itemJson["modifiers"])
			{
				auto stat = common::entities::getStat(modifierJson["attribute"]);
				auto scope = common::entities::getScope(modifierJson["scope"]);
				auto val = modifierJson["value"];
				Modifier modifier;
				switch (stat)
				{
				case common::entities::Stat::Trigger:
					modifier = {stat, scope, getTrigger(val)};
					modifiers.push_back(modifier);
					break;
				default:
					modifier = {stat, scope, val};
					modifiers.push_back(modifier);
					break;
				}
			}
			Item itemData = {itemJson["name"], modifiers, itemJson["id"], itemJson["x"], itemJson["y"], itemJson["width"], itemJson["height"]};
			itemsData[itemJson["id"]] = itemData;
		}
	}

	float getTrigger(std::string trigger)
	{
		auto it = mapTrigger.find(trigger);
		if (it != mapTrigger.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Trigger::OnNone);
	}

	Item ItemsLoader::getItem(int id) { return itemsData[id]; }
	sf::Sprite ItemsLoader::getSprite(int id)
	{
		Item item = itemsData[id];
		sf::Sprite sprite(texture);
		int gridSize = 16;
		sprite.setOrigin({static_cast<float>(item.width * gridSize / 2), static_cast<float>(item.height * gridSize / 2)});
		sprite.setTextureRect(sf::IntRect({item.x * gridSize, item.y * gridSize}, {item.width * gridSize, item.height * gridSize}));
		sprite.setScale({3.f, 3.f});
		return sprite;
	}
}  // namespace features::item
