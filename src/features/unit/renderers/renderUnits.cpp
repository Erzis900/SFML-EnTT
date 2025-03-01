#include "renderUnits.hpp"
#include "components/visible.hpp"

namespace features::unit::renderers
{
	constexpr float pi = acos(-1);
	void renderUnits(entt::registry &registry, sf::RenderWindow &window, UnitsLoader &unitsLoader)
	{
		auto view = registry.view<common::components::unit, common::components::position, common::components::lookDirection, common::components::renderable,
								  common::components::visible>();

		for (auto [entity, unit, pos, dir, render] : view.each())
		{
			auto sprite = unitsLoader.getSprite(unit.id);
			auto width = sprite.getTextureRect().size.x;
			auto height = sprite.getTextureRect().size.y;

			auto rotation = sf::degrees(std::atan2(dir.y, dir.x) * 180 / pi) - sf::degrees(dir.y == 0 && dir.x == 0 ? 0 : -90);
			auto posX = width / 2.f;
			auto posY = height / 2.f;

			sprite.setOrigin({posX, posY});
			sprite.setRotation(rotation);
			sprite.setPosition({pos.x, pos.y});
			window.draw(sprite);
		}
	}
}  // namespace features::unit::renderers
