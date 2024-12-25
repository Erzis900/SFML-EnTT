#include "applyUnitStat.hpp"
#include "components/unit.hpp"
#include "components/children.hpp"
#include "components/speed.hpp"
#include "entities/attribute.hpp"

namespace common::systems
{
    void applyUnitStat(entt::registry &registry)
    {
        auto view = registry.view<common::components::unit, common::components::children<common::entities::ATTRIBUTES_COUNT>, common::components::speed>();

        for (auto [entity, unit, children, speed] : view.each())
        {
            auto &child_speed = registry.get<common::components::speed>(children.entities[static_cast<std::size_t>(common::entities::Stat::Speed)]);

            registry.emplace_or_replace<common::components::speed>(entity, child_speed.value);
        }
    }
}