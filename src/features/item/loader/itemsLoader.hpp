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
        Item getItem(int id);
        sf::Sprite getSprite(int id);
    private:
        std::map<int, Item> itemsData = {};
        sf::Texture texture;
    };


}