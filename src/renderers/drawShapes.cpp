#include "drawShapes.hpp"

namespace common::renderers
{
	void drawShapes(entt::registry &registry, sf::RenderWindow &window, features::item::ItemsLoader &itemsLoader)
	{
		auto view = registry.view<common::components::position, common::components::renderable, common::components::shape, common::components::direction>();

		for (auto [entity, pos, render, shape, dir] : view.each())
		{
			shape.shape.setPosition({pos.x, pos.y});
			window.draw(shape.shape);
		}
	}
}  // namespace common::renderers
