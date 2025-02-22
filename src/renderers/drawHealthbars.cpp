#include "drawHealthbars.hpp"

namespace common::renderers
{
	void drawHealthbars(entt::registry &registry, sf::RenderWindow &window)
	{
		auto view = registry.view<common::components::renderable, common::components::collider, common::components::position, common::components::health,
								  common::components::maxHealth>();

		const int healthbarWidth = 60;
		const int healthbarHeight = 5;

		sf::RectangleShape healthbar;
		healthbar.setSize({healthbarWidth, healthbarHeight});
		healthbar.setFillColor(sf::Color::Red);

		sf::RectangleShape currentHealth;
		currentHealth.setFillColor(sf::Color::Green);

		for (auto [entity, render, collider, pos, health, maxHealth] : view.each())
		{
			float xPos = pos.x - healthbarWidth / 2;
			float yPos = pos.y - collider.radius - 18;

			healthbar.setPosition({xPos, yPos});
			currentHealth.setSize({healthbarWidth * health.value / maxHealth.value, healthbarHeight});
			currentHealth.setPosition({xPos, yPos});

			window.draw(healthbar);
			window.draw(currentHealth);
		}
	}
}  // namespace common::renderers