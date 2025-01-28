#include "cleanupRemoved.hpp"
#include "components/remove.hpp"

namespace common::systems
{
    void cleanupRemoved(entt::registry &registry)
    {
        auto view = registry.view<common::components::remove>();

        for (auto [entity] : view.each())
        {
            registry.destroy(entity);
        }
    }
}  // namespace common::systems
