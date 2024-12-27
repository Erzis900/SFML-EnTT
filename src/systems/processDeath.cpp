#include "processDeath.hpp"
#include "components/health.hpp"

namespace common::systems
{
    void processDeath(entt::registry &registry)
    {
        auto view = registry.view<common::components::health>();

        for (auto [entity, health] : view.each())
        {
            if (health.value <= 0.f)
            {
                registry.destroy(entity);
            }
        }
    }
}