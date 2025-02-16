#include "unitsLoader.hpp"

namespace features::unit
{
	UnitsLoader::UnitsLoader()
	{
		std::ifstream unitsFile("../../data/units.json");
		nlohmann::json data = nlohmann::json::parse(unitsFile);
		texture = sf::Texture("../../assets/units.png", false, sf::IntRect({0, 0}, {16 * 3, 16 * 2}));

		for (auto &unitJson : data)
		{
			Unit unitData = {unitJson["name"],
							 unitJson["id"],
							 unitJson["x"],
							 unitJson["y"],
							 unitJson["head"],
							 unitJson["chest"],
							 unitJson["mainShoulder"],
							 unitJson["offShoulder"],
							 unitJson["mainhand"],
							 unitJson["offhand"],
							 unitJson["cape"],
							 3,
							 2,
							 unitJson["inventory"]};
			unitsData[unitJson["id"]] = unitData;
		}
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
		registry.emplace<common::components::direction>(entity, 0.f, 0.f);
		registry.emplace<common::components::lookDirection>(entity, 0.f, 0.f);

		common::entities::initAttributes(registry, entity);

		return entity;
	}

	entt::entity UnitsLoader::createUnit(entt::registry &registry, int id, float x, float y)
	{
		auto entity = createUnit(registry, id);
		registry.emplace<common::components::renderable>(entity);
		registry.emplace<common::components::position>(entity, x, y);
		registry.emplace<features::map::components::rectCollider>(entity, 100.f, 100.f);

		return entity;
	}

	entt::entity UnitsLoader::createUnit(entt::registry &registry, features::item::ItemsLoader &itemsLoader, int id, float x, float y)
	{
		auto entity = createUnit(registry, id, x, y);
		equipItems(registry, itemsLoader, id, entity);
		return entity;
	}

	void UnitsLoader::equipItems(entt::registry &registry, features::item::ItemsLoader &itemsLoader, int id, entt::entity entity)
	{
		auto unit = getUnit(id);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.mainhand, features::item::components::SlotType::Mainhand, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.offhand, features::item::components::SlotType::Offhand, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.cape, features::item::components::SlotType::Cape, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.head, features::item::components::SlotType::Head, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.mainShoulder, features::item::components::SlotType::MainShoulder, true);
		features::item::entities::equipItem(registry, itemsLoader, entity, unit.offShoulder, features::item::components::SlotType::OffShoulder, true);
	}
}  // namespace features::unit
