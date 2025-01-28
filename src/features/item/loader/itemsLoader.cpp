#include "itemsLoader.hpp"

namespace features::item {
    ItemsLoader::ItemsLoader() {
        std::ifstream itemsFile("../../data/items.json");
        nlohmann::json data = nlohmann::json::parse(itemsFile);
        texture = sf::Texture("../../assets/items.png", false, sf::IntRect({ 0, 0 }, { 512, 512 }));

        for (auto& itemJson : data) {
            Item itemData = {
                itemJson["id"],
                itemJson["name"],
                itemJson["damage"],
                itemJson["x"],
                itemJson["y"],
                itemJson["width"],
                itemJson["height"]
            };
            itemsData[itemJson["id"]] = itemData;
        }
    }
}