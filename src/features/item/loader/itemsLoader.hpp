#pragma once

#include "pch.hpp"


namespace features::item {
    struct Item {
        int id;
        std::string name;
        float damage;
        int x;
        int y;
        int width;
        int height;
    };
    class ItemsLoader {
    public:
        ItemsLoader();
        Item getItem(int id) {
            return itemsData[id];
        }
        sf::Sprite getSprite(int id) {
            Item item = itemsData[id];
            sf::Sprite sprite(texture);
            sprite.setOrigin({ float(item.width * 8), float(item.height * 8) });
            sprite.setTextureRect(sf::IntRect({ item.x * 16, item.y * 16 }, { item.width * 16, item.height * 16 }));
            sprite.setScale({ 3.f, 3.f });
            return sprite;
        }
    private:
        std::map<int, Item> itemsData = {};
        sf::Texture texture;
    };


}