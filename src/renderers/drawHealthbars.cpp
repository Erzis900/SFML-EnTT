#include <SFML/Graphics.hpp>

#include "external/entt.hpp"

#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/position.hpp"
#include "components/shape.hpp"

namespace common::renderers
{
    void drawHealthbars(entt::registry &registry, sf::RenderWindow &window)
    {
        auto view = registry.view<common::components::position, common::components::health, common::components::maxHealth, common::components::shape>();

        for (auto [entity, pos, health, maxHealth, shape] : view.each())
        {
            sf::RectangleShape healthbar;
            healthbar.setSize({maxHealth.value, 5});
            healthbar.setFillColor(sf::Color::Red);
            healthbar.setPosition(pos.x - shape.value.getRadius(), pos.y - shape.value.getRadius() - 24);

            sf::RectangleShape currentHealth;
            currentHealth.setSize({health.value, 5});
            currentHealth.setFillColor(sf::Color::Green);
            currentHealth.setPosition(pos.x - shape.value.getRadius(), pos.y - shape.value.getRadius() - 24);

            window.draw(healthbar);
            window.draw(currentHealth);
        }
    }
}