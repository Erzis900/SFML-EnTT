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
			Item itemData = {itemJson["id"], itemJson["name"], itemJson["x"], itemJson["y"], itemJson["width"], itemJson["height"]};
			itemsData[itemJson["id"]] = itemData;
		}
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
