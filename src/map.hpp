#pragma once
#include "pch.hpp"

class Map
{
  public:
	Map(std::string mapPath, std::string tilesetPath);

	void drawMap(sf::RenderWindow &window);

  private:
	std::vector<std::vector<unsigned int>> tilemap;

	unsigned int height, width;
	sf::Texture tileset;

	sf::Vector2i tileSize;
	sf::Vector2i tilesetSize;

	float scalingFactor;

	void drawTile(sf::RenderWindow &window, unsigned int id, int x, int y);
};