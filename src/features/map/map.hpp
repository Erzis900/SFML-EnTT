#pragma once
#include "pch.hpp"

namespace features::map
{
	class Map
	{
	  public:
		Map(std::string mapPath, std::string tilesetPath);

		void setupMap(entt::registry &registry);
		void drawBackground(sf::RenderWindow &window);

		sf::Vector2i getMapDim() { return {static_cast<int>(width * tileSize.x * scalingFactor), static_cast<int>(height * tileSize.y * scalingFactor)}; }

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

		void loadTilemap(nlohmann::json &data, unsigned int layerNo);
		void setupTile(unsigned int id, int x, int y);

		int noColliders;
	};
}  // namespace features::map