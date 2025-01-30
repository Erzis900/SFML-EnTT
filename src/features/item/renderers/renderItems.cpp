#include "renderItems.hpp"

namespace features::item::renderers
{
	void renderItems(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<features::item::components::equipped>();

		for (auto [entity, equipped] : view.each())
		{
			auto try_unit = registry.try_get<common::components::unit>(equipped.unit);
			if (!try_unit)
			{
				registry.emplace<common::components::remove>(entity);
				continue;
			}
			auto pos = registry.get<common::components::position>(equipped.unit);
			auto dir = registry.get<common::components::direction>(equipped.unit);
			auto sprite = itemsLoader.getSprite(equipped.itemId);
			auto width = sprite.getTextureRect().size.x;
			auto height = sprite.getTextureRect().size.y;
			sprite.setRotation(sf::degrees(std::atan2(dir.y, dir.x) * 180 / M_PI) - sf::degrees(dir.y == 0 && dir.x == 0 ? 0 : -90));
			if (equipped.slot == features::item::components::SlotType::Mainhand)
			{
				sprite.setOrigin({(-30.f + width / 2.f), (15.f + height / 2.f)});
				sprite.setPosition({pos.x, pos.y});
			}
			else if (equipped.slot == features::item::components::SlotType::Offhand)
			{
				sprite.setOrigin({(30.f + width / 2.f), (15.f + height / 2.f)});
				sprite.setPosition({pos.x, pos.y});
			}
			else
			{
				sprite.setPosition({pos.x, pos.y});
			}
			window.draw(sprite);
		}
	}
}  // namespace features::item::renderers
