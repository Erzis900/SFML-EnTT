
#include "recalculateStat.hpp"
#include <iostream>

namespace common::systems
{
    void recalculateStat(entt::registry &registry)
    {
        auto view = registry.view<common::components::attribute, common::components::recalculate, common::components::relationship>();

        for (auto [entity, attr, recalc, relation] : view.each())
        {
            auto &relationship = registry.get<common::components::relationship>(entity);
            auto &attribute = registry.get<common::components::attribute>(entity);
            auto modifier = relationship.first_child;

            auto value = attribute.baseValue;
            while (modifier != entt::null)
            {
                const auto &mod = registry.get<common::components::modifier>(modifier);
                switch (mod.scope)
                {
                case common::components::Scope::Flat:
                    value += mod.value;
                    break;
                case common::components::Scope::PercentAdd:
                    value += attr.baseValue * mod.value;
                    break;
                case common::components::Scope::PercentMult:
                    value *= 1 + mod.value;
                    break;
                default:
                    break;
                }

                modifier = registry.get<common::components::relationship>(modifier).next;
            }

            std::cout << "Entity " << static_cast<int>(entity) << " attribute value: " << registry.get<common::components::attribute>(entity).value << std::endl;
            registry.replace<common::components::attribute>(entity, attr.baseValue, value);
            std::cout << "Entity " << static_cast<int>(entity) << " attribute value: " << registry.get<common::components::attribute>(entity).value << std::endl;
            registry.remove<common::components::recalculate>(entity);
        }
    }
}
