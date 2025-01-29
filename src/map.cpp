#include "map.hpp"

Map::Map(std::string mapPath, std::string tilesetPath)
{
	std::ifstream mapFile(mapPath);
	nlohmann::json data = nlohmann::json::parse(mapFile);

	height = data["layers"][0]["height"];
	width = data["layers"][0]["width"];

	tilemap.resize(height);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			tilemap[i].push_back(data["layers"][0]["data"][i * width + j]);
		}
	}

	tileset = sf::Texture(tilesetPath);

	tileSize = {16, 16};

	// whole tileset is 1024x640
	tilesetSize = {64, 40};

	scalingFactor = 4.f;
}

void Map::drawMap(sf::RenderWindow &window)
{
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			drawTile(window, tilemap[i][j], j, i);
		}
	}
}

void Map::drawTile(sf::RenderWindow &window, unsigned int id, int x, int y)
{
	sf::Sprite sprite(tileset);

	int tileRow = id / tilesetSize.x;
	int tileCol = id % tilesetSize.x - 1;

	sf::Vector2i tilePos = {tileCol * tileSize.x, tileRow * tileSize.y};

	sprite.setTextureRect(sf::IntRect(tilePos, tileSize));
	sprite.setScale({scalingFactor, scalingFactor});
	sprite.setPosition(sf::Vector2f(x * tileSize.x * scalingFactor, y * tileSize.y * scalingFactor));

	window.draw(sprite);
}