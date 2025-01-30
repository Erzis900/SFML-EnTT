#pragma once
#include "pch.hpp"

class Map
{
  public:
	Map(std::string mapPath, std::string tilesetPath);

	void setupMap();
	void drawBackground(sf::RenderWindow &window);

  private:
	std::vector<std::vector<unsigned int>> tilemap;

	unsigned int height, width;
	sf::Texture tileset;

	sf::RenderTexture bg;

	sf::Vector2i tileSize;
	sf::Vector2i tilesetSize;

	float scalingFactor;
	sf::View camera;

	void setupTile(unsigned int id, int x, int y);
};