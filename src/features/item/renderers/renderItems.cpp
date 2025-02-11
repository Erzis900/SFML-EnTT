#include "renderItems.hpp"

namespace features::item::renderers
{
	constexpr float pi = acos(-1);
	void renderItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		renderGroundItems(registry, window, itemsLoader);
		renderEquippedItems(registry, window, itemsLoader);
	}

	void renderEquippedItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<features::item::components::equipped, features::item::components::itemId, common::components::renderable>();

		for (auto [entity, equipped, itemId, renderable] : view.each())
		{
			auto pos = registry.get<common::components::position>(equipped.unit);
			auto dir = registry.get<common::components::lookDirection>(equipped.unit);
			auto sprite = itemsLoader.getSprite(itemId.id);
			auto width = sprite.getTextureRect().size.x;
			auto height = sprite.getTextureRect().size.y;

			auto rotation = sf::degrees(std::atan2(dir.y, dir.x) * 180 / pi) - sf::degrees(dir.y == 0 && dir.x == 0 ? 0 : -90);
			auto posX = width / 2.f;
			auto posY = height / 2.f;
			switch (equipped.slot)
			{
			case features::item::components::SlotType::Head:
				sprite.setOrigin({posX, posY});
				sprite.setRotation(rotation);
				break;
			case features::item::components::SlotType::Chest:
				sprite.setOrigin({posX, posY});
				sprite.setRotation(rotation);
				break;
			case features::item::components::SlotType::MainShoulder:
				sprite.setOrigin({posX - 21.f, posY});
				sprite.setRotation(rotation);
				break;
			case features::item::components::SlotType::OffShoulder:
				sprite.setOrigin({posX - 20.f, posY});
				sprite.setScale({-sprite.getScale().x, sprite.getScale().y});
				sprite.setRotation(rotation);
				break;
			case features::item::components::SlotType::Mainhand:
				sprite.setOrigin({posX - 26.f, posY - 5.f});
				sprite.setRotation(rotation - sf::degrees(60.f));
				break;
			case features::item::components::SlotType::Offhand:
				sprite.setOrigin({posX + 15.f, posY + 25.f});
				sprite.setRotation(rotation - sf::degrees(30.f));
				/**
				 * if (quiver)
					sprite.setOrigin({posX + 25.f, posY - 25.f});
					sprite.setRotation(rotation - sf::degrees(-60.f));
				 * else
					sprite.setOrigin({posX + 15.f, posY + 25.f});
					sprite.setRotation(rotation - sf::degrees(30.f));
				 */
				break;
			case features::item::components::SlotType::Cape:
				sprite.setOrigin({posX, posY - 15.f});
				sprite.setRotation(rotation);
				break;
			default:
				sprite.setRotation(rotation);
				break;
			}

			sprite.setPosition({pos.x, pos.y});
			window.draw(sprite);
		}
	}

	void renderGroundItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<common::components::position, features::item::components::itemId>();
		for (auto [entity, pos, itemId] : view.each())
		{
			auto sprite = itemsLoader.getSprite(itemId.id);
			sprite.setPosition({pos.x, pos.y});
			window.draw(sprite);
		}
	}
}  // namespace features::item::renderers
