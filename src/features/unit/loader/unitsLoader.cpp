#include "unitsLoader.hpp"

namespace features::unit
{
	UnitsLoader::UnitsLoader()
	{
		for (const auto &entry : std::filesystem::directory_iterator("../../src/content/units"))
		{
			auto id = std::stoi(entry.path().filename().replace_extension().string());
			if (entry.path().extension() == ".json")
			{
				std::ifstream unitsFile(entry.path());
				nlohmann::json unitJson = nlohmann::json::parse(unitsFile);
				auto unit = unitJson["unit"];
				Unit unitData = {
					unitJson["name"],
					id,
					unit["x"],
					unit["y"],
					unit["head"],
					unit["chest"],
					unit["cape"],
					unit["mainShoulder"],
					unit["offShoulder"],
					unit["mainhand"],
					unit["offhand"],
					3,
					2,
					//  unitJson["inventory"],
				};
				unitsData[id] = unitData;
			}
		}
		texture = sf::Texture("../../public/units.png", false, sf::IntRect({0, 0}, {16 * 3, 16 * 2}));
	}

	Unit UnitsLoader::getUnit(int id) { return unitsData[id]; }
	sf::Sprite UnitsLoader::getSprite(int id)
	{
		Unit unit = unitsData[id];
		sf::Sprite sprite(texture);
		int gridSize = 16;
		sprite.setOrigin({static_cast<float>(unit.width * gridSize / 2), static_cast<float>(unit.height * gridSize / 2)});
		sprite.setTextureRect(sf::IntRect({unit.x * gridSize, unit.y * gridSize}, {unit.width * gridSize, unit.height * gridSize}));
		sprite.setScale({3.f, 3.f});
		return sprite;
	}

	entt::entity UnitsLoader::createUnit(entt::registry &registry, int id)
	{
		auto entity = registry.create();
		registry.emplace<common::components::unit>(entity, id);
		registry.emplace<common::components::direction>(entity, 0.f, 0.f, true);
		registry.emplace<common::components::lookDirection>(entity, 0.f, 0.f);

		registry.emplace<common::components::pointsAt>(entity, sf::Vector2f(0.f, 0.f));
		registry.emplace<effect::components::effects>(entity);

		common::entities::initAttributes(registry, entity);

		return entity;
	}

	entt::entity UnitsLoader::createUnit(entt::registry &registry, int id, float x, float y)
	{
		auto entity = createUnit(registry, id);
		registry.emplace<common::components::renderable>(entity);
		registry.emplace<common::components::position>(entity, x, y);
		registry.emplace<map::components::rectCollider>(entity, 100.f, 100.f);

		return entity;
	}

	entt::entity UnitsLoader::createUnit(entt::registry &registry, item::ItemsLoader &itemsLoader, int id, float x, float y)
	{
		auto entity = createUnit(registry, id, x, y);
		equipItems(registry, itemsLoader, id, entity);
		return entity;
	}

	void UnitsLoader::equipItems(entt::registry &registry, item::ItemsLoader &itemsLoader, int id, entt::entity entity)
	{
		auto unit = getUnit(id);
		item::entities::equipItem(registry, itemsLoader, entity, unit.mainhand, item::components::SlotType::Mainhand, true);
		item::entities::equipItem(registry, itemsLoader, entity, unit.offhand, item::components::SlotType::Offhand, true);
		item::entities::equipItem(registry, itemsLoader, entity, unit.cape, item::components::SlotType::Cape, true);
		item::entities::equipItem(registry, itemsLoader, entity, unit.head, item::components::SlotType::Head, true);
		item::entities::equipItem(registry, itemsLoader, entity, unit.mainShoulder, item::components::SlotType::MainShoulder, true);
		item::entities::equipItem(registry, itemsLoader, entity, unit.offShoulder, item::components::SlotType::OffShoulder, true);
	}
}  // namespace features::unit
