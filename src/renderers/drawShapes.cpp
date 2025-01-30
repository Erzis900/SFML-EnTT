#include "drawShapes.hpp"

namespace common::renderers
{
	void drawShapes(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<common::components::position, common::components::renderable, common::components::direction>();

		for (auto [entity, pos, render, dir] : view.each())
		{
			render.shape.setPosition({pos.x, pos.y});
			window.draw(render.shape);
		}
	}
}  // namespace common::renderers
