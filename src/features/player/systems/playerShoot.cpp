#include "playerShoot.hpp"
#include "../components/playerControlled.hpp"
#include "components/position.hpp"
#include "components/direction.hpp"
#include "entities/projectile.hpp"

namespace features::player::systems
{
    void playerShoot(entt::registry &registry, sf::RenderWindow &window)
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            auto view = registry.view<common::components::position, features::player::components::playerControlled>();
            auto playerEntity = *view.begin();
            auto &playerPos = view.get<common::components::position>(playerEntity);

            sf::Vector2f mousePos = (sf::Vector2f)sf::Mouse::getPosition(window);
            sf::Vector2f dirVec = {mousePos.x - playerPos.x, mousePos.y - playerPos.y};

            float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
            if (magnitude > 0)
            {
                dirVec.x /= magnitude;
                dirVec.y /= magnitude;
            }

            common::components::direction dir(dirVec.x, dirVec.y);
            common::entities::createProjectile(registry, playerPos, dir);
        }
    }
}