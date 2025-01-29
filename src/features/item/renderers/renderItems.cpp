#include "renderItems.hpp"

namespace features::item::renderers
{
	void renderItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<features::item::components::equipped>();

		for (auto [entity, equipped] : view.each())
		{
			auto pos = registry.get<common::components::position>(equipped.unit);
			auto dir = registry.get<common::components::direction>(equipped.unit);
			sf::Sprite sprite = itemsLoader.getSprite(equipped.itemId);
			if (equipped.slot == features::item::components::SlotType::Mainhand)
			{
				sprite.setPosition({pos.x + 50, pos.y + 10});
			}
			else if (equipped.slot == features::item::components::SlotType::Offhand)
			{
				sprite.setPosition({pos.x - 50, pos.y - 10});
			}
			else
			{
				sprite.setPosition({pos.x, pos.y});
			}
			sprite.setRotation(sf::degrees(std::atan2(dir.y, dir.x) * 180 / M_PI) - sf::degrees(dir.y == 0 && dir.x == 0 ? 0 : -90));
			window.draw(sprite);
		}
	}
}  // namespace features::item::renderers
