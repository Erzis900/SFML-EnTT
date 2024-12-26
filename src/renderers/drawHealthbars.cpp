#include <SFML/Graphics.hpp>

#include "external/entt.hpp"

#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/position.hpp"

namespace common::renderers
{
    void drawHealthbars(entt::registry &registry, sf::RenderWindow &window)
    {
        auto view = registry.view<common::components::position, common::components::health, common::components::maxHealth>();

        for (auto [entity, pos, health, maxHealth] : view.each())
        {
        }
    }
}