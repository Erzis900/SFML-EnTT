#include "map.hpp"
#include "components/collider.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "entities/tileCollider.hpp"

namespace features::map
{
	Map::Map(std::string mapPath, std::string tilesetPath)
	{
		std::ifstream mapFile(mapPath);
		data = nlohmann::json::parse(mapFile);

		noLayers = data["layers"].size();

		height = data["layers"][0]["height"];
		width = data["layers"][0]["width"];

		tileset = sf::Texture(tilesetPath);

		tileSize = {16, 16};

		// whole tileset is 1024x640
		tilesetSize = {64, 40};

		scalingFactor = 4.f;
		bg = sf::RenderTexture({static_cast<unsigned int>(width * tileSize.x * scalingFactor), static_cast<unsigned int>(height * tileSize.y * scalingFactor)});
		noColliders = 0;
	}

	void Map::setupMap(entt::registry &registry)
	{
		for (int layerNo = 0; layerNo < noLayers; layerNo++)
		{
			loadTilemap(data, layerNo);
			for (int i = 0; i < height; i++)
			{
				for (int j = 0; j < width; j++)
				{
					setupTile(tilemap[i][j], j, i);

					if (tilemap[i][j] == 2591)
					{
						features::map::entities::createColliderTile(tilemap[i][j], j, i, tileSize.x, scalingFactor, registry);
						noColliders++;
					}
				}
			}
		}

		bg.display();
	}

	void Map::drawBackground(sf::RenderWindow &window)
	{
		sf::Sprite background(bg.getTexture());
		window.draw(background);
	}

	void Map::loadTilemap(nlohmann::json &data, unsigned int layerNo)
	{
		height = data["layers"][layerNo]["height"];
		width = data["layers"][layerNo]["width"];

		tilemap.clear();
		tilemap.resize(height);

		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				tilemap[i].push_back(data["layers"][layerNo]["data"][i * width + j]);
			}
		}
	}

	void Map::setupTile(unsigned int id, int x, int y)
	{
		sf::Sprite sprite(tileset);

		int tileRow = id / tilesetSize.x;
		int tileCol = id % tilesetSize.x - 1;

		sf::Vector2i tilePos = {tileCol * tileSize.x, tileRow * tileSize.y};

		sprite.setTextureRect(sf::IntRect(tilePos, tileSize));
		sprite.setScale({scalingFactor, scalingFactor});
		sprite.setPosition(sf::Vector2f(x * tileSize.x * scalingFactor, y * tileSize.y * scalingFactor));

		bg.draw(sprite);
		// window.draw(sprite);
	}
}  // namespace features::map