#include "drawHealthbars.hpp"

namespace common::renderers
{
	void drawHealthbars(entt::registry &registry, sf::RenderWindow &window)
	{
		auto view = registry.view<common::components::renderable, common::components::collider, common::components::position, common::components::health,
								  common::components::maxHealth>();

		for (auto [entity, render, collider, pos, health, maxHealth] : view.each())
		{
			sf::RectangleShape healthbar;
			healthbar.setSize({60, 5});
			healthbar.setFillColor(sf::Color::Red);
			healthbar.setPosition({pos.x - healthbar.getSize().x / 2, pos.y - collider.radius - 18});

			sf::RectangleShape currentHealth;
			currentHealth.setSize({60 * health.value / maxHealth.value, 5});
			currentHealth.setFillColor(sf::Color::Green);
			currentHealth.setPosition({pos.x - healthbar.getSize().x / 2, pos.y - collider.radius - 18});

			window.draw(healthbar);
			window.draw(currentHealth);
		}
	}
}  // namespace common::renderers