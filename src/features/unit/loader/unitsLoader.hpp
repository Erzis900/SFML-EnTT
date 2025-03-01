#pragma once

#include "pch.hpp"

#include "components/direction.hpp"
#include "components/lookDirection.hpp"
#include "components/pointsAt.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"
#include "components/unit.hpp"
#include "entities/attribute.hpp"

#include "features/effect/components/effects.hpp"
#include "features/item/entities/item.hpp"
#include "features/item/loader/itemsLoader.hpp"
#include "features/map/components/rectCollider.hpp"

namespace features::unit
{
	struct Unit
	{
		std::string name;
		int id;
		int x;
		int y;
		int head;
		int chest;
		int cape;
		int mainShoulder;
		int offShoulder;
		int mainhand;
		int offhand;
		int width;
		int height;
		// std::array<int, 16> inventory;
	};

	class UnitsLoader
	{
	  public:
		UnitsLoader();
		Unit getUnit(int id);
		sf::Sprite getSprite(int id);
		entt::entity createUnit(entt::registry &registry, int id);
		entt::entity createUnit(entt::registry &registry, int id, float x, float y);
		entt::entity createUnit(entt::registry &registry, item::ItemsLoader &itemsLoader, int id, float x, float y);
		void equipItems(entt::registry &registry, item::ItemsLoader &itemsLoader, int id, entt::entity entity);

	  private:
		std::map<int, Unit> unitsData = {};
		sf::Texture texture;
	};

}  // namespace features::unit