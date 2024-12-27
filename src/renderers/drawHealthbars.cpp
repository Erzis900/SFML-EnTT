#include "drawHealthbars.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/position.hpp"
#include "components/renderable.hpp"

namespace common::renderers
{
    void drawHealthbars(entt::registry &registry, sf::RenderWindow &window)
    {
        auto view = registry.view<common::components::position, common::components::health, common::components::maxHealth, common::components::renderable>();

        for (auto [entity, pos, health, maxHealth, render] : view.each())
        {
            sf::RectangleShape healthbar;
            healthbar.setSize({maxHealth.value, 5});
            healthbar.setFillColor(sf::Color::Red);
            healthbar.setPosition(pos.x - render.shape.getRadius(), pos.y - render.shape.getRadius() - 24);

            sf::RectangleShape currentHealth;
            currentHealth.setSize({health.value, 5});
            currentHealth.setFillColor(sf::Color::Green);
            currentHealth.setPosition(pos.x - render.shape.getRadius(), pos.y - render.shape.getRadius() - 24);

            window.draw(healthbar);
            window.draw(currentHealth);
        }
    }
}