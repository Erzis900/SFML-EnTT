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

				std::vector<common::entities::Modifier> modifiers = {};
				for (auto &modifierJson : itemJson["modifiers"])
				{
					auto attribute = modifierJson["value"];
					auto stat = common::entities::getStat(attribute["attribute"]);
					auto scope = common::entities::getScope(attribute["scope"]);
					auto val = attribute["value"];
					float value = 0.f;
					common::entities::Modifier modifier;
					switch (stat)
					{
					case common::entities::Stat::Place:
						value = getPlace(val);
						break;
					case common::entities::Stat::Group:
						value = getGroup(val);
						break;
					case common::entities::Stat::Travel:
						value = getTravel(val);
						break;
					case common::entities::Stat::Moment:
						value = getMoment(val);
						break;
					case common::entities::Stat::Trigger:
						value = getTrigger(val);
						break;
					case common::entities::Stat::Area:
						value = getArea(val);
						break;
					case common::entities::Stat::Kind:
						value = getKind(val);
						break;
					default:
						value = val;
						break;
					}
					modifier = {stat, scope, value};
					modifiers.push_back(modifier);
				}
				Item itemData = {itemJson["name"],
								 modifiers,
								 getSlot(itemJson["slot"]),
								 getType(itemJson["type"]),
								 id,
								 itemJson["sprite"]["x"],
								 itemJson["sprite"]["y"],
								 itemJson["sprite"]["width"],
								 itemJson["sprite"]["height"],
								 itemJson["dropChance"]};
				itemsData[id] = itemData;
			}
		}
		texture = sf::Texture("../../public/items.png", false, sf::IntRect({0, 0}, {512, 512}));
	}

	float getPlace(std::string place)
	{
		auto it = mapPlace.find(place);
		if (it != mapPlace.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Place::None);
	}

	float getGroup(std::string group)
	{
		auto it = mapGroup.find(group);
		if (it != mapGroup.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Group::None);
	}

	float getTravel(std::string travel)
	{
		auto it = mapTravel.find(travel);
		if (it != mapTravel.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Travel::None);
	}

	float getMoment(std::string moment)
	{
		auto it = mapMoment.find(moment);
		if (it != mapMoment.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Moment::None);
	}

	float getTrigger(std::string trigger)
	{
		auto it = mapTrigger.find(trigger);
		if (it != mapTrigger.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Trigger::None);
	}

	float getArea(std::string area)
	{
		auto it = mapArea.find(area);
		if (it != mapArea.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Area::None);
	}

	float getKind(std::string kind)
	{
		auto it = mapKind.find(kind);
		if (it != mapKind.end())
		{
			return static_cast<float>(it->second);
		}
		return static_cast<float>(Kind::None);
	}

	Type getType(std::string type)
	{
		auto it = mapType.find(type);
		if (it != mapType.end())
		{
			return it->second;
		}
		return Type::None;
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
