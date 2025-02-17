#include "itemsLoader.hpp"

namespace features::item
{
	ItemsLoader::ItemsLoader()
	{
		for (const auto &entry : std::filesystem::directory_iterator("../../src/content/items"))
		{
			auto id = std::stoi(entry.path().filename().replace_extension().string());
			if (entry.path().extension() == ".json")
			{
				std::ifstream itemsFile(entry.path());
				nlohmann::json itemJson = nlohmann::json::parse(itemsFile);

				std::vector<Modifier> modifiers = {};
				for (auto &modifierJson : itemJson["modifiers"])
				{
					auto attribute = modifierJson["value"];
					auto stat = common::entities::getStat(attribute["attribute"]);
					auto scope = common::entities::getScope(attribute["scope"]);
					auto val = attribute["value"];
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
				Item itemData = {itemJson["name"],
								 modifiers,
								 getSlot(itemJson["slot"]),
								 getType(itemJson["type"]),
								 id,
								 itemJson["sprite"]["x"],
								 itemJson["sprite"]["y"],
								 itemJson["sprite"]["width"],
								 itemJson["sprite"]["height"]};
				itemsData[id] = itemData;
			}
		}
		texture = sf::Texture("../../public/items.png", false, sf::IntRect({0, 0}, {512, 512}));
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

	Type getType(std::string type)
	{
		auto it = mapType.find(type);
		if (it != mapType.end())
		{
			return it->second;
		}
		return Type::NoItem;
	}

	components::SlotType getSlot(std::string slot)
	{
		auto it = mapSlot.find(slot);
		if (it != mapSlot.end())
		{
			return it->second;
		}
		return components::SlotType::NoSlot;
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
