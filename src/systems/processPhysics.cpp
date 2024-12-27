#include "processPhysics.hpp"
#include "components/position.hpp"
#include "components/collider.hpp"
#include "components/speed.hpp"

namespace common::systems
{
    void processPhysics(entt::registry &registry, float deltaTime)
    {
        auto view = registry.view<common::components::position, common::components::collider, common::components::speed>();

        for (auto [entityA, posA, collA, speedA] : view.each())
        {
            for (auto [entityB, posB, collB, speedB] : view.each())
            {
                float deltaX = posB.x - posA.x;
                float deltaY = posB.y - posA.y;
                float distance = std::sqrt(deltaX * deltaX + deltaY * deltaY);
                if (distance < (collA.radius + collB.radius) && entityA != entityB)
                {
                    sf::Vector2f dirVec = {posA.x - posB.x, posA.y - posB.y};

                    float magnitude = std::sqrt(dirVec.x * dirVec.x + dirVec.y * dirVec.y);
                    if (magnitude > 0)
                    {
                        dirVec.x /= magnitude;
                        dirVec.y /= magnitude;
                    }

                    posA.x += dirVec.x * speedA.value * deltaTime;
                    posA.y += dirVec.y * speedA.value * deltaTime;
                    posB.x -= dirVec.x * speedB.value * deltaTime;
                    posB.y -= dirVec.y * speedB.value * deltaTime;
                }
            }
        }
    }
}