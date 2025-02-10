#pragma once
#include "pch.hpp"

namespace features::map
{
	class Map
	{
	  public:
		Map(std::string mapPath, std::string tilesetPath);

		void setupMap();
		void drawBackground(sf::RenderWindow &window);
		void loadTilemap(nlohmann::json &data, unsigned int layerNo);

	  private:
		std::vector<std::vector<unsigned int>> tilemap;
		unsigned int noLayers;

		unsigned int height, width;
		sf::Texture tileset;

		sf::RenderTexture bg;

		sf::Vector2i tileSize;
		sf::Vector2i tilesetSize;

		float scalingFactor;
		sf::View camera;

		nlohmann::json data;

		void setupTile(unsigned int id, int x, int y);
	};
}  // namespace features::map