#include "recalculateStat.hpp"

#include "components/attribute.hpp"
#include "components/modifiers.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"

#include "entities/attribute.hpp"

namespace common::systems {
    void recalculateStat(entt::registry &registry)
    {
        auto view = registry.view<common::components::attribute, common::components::recalculate, common::components::relationship>();

        for (auto [entity, attr, recalc, relation] : view.each())
        {
            auto &relationship = registry.get<common::components::relationship>(entity);
            auto &attribute = registry.get<common::components::attribute>(entity);
            auto modifier = relationship.first_child;

            auto value = attribute.baseValue;
            std::vector<common::components::modifier> mods;
            while (modifier != entt::null)
            {
                const auto &mod = registry.get<common::components::modifier>(modifier);
                mods.push_back(mod);

                modifier = registry.get<common::components::relationship>(modifier).next;
            }

            sort(mods.begin(), mods.end(), [](const common::components::modifier &a, const common::components::modifier &b) { return a.scope < b.scope; });

            for (const auto &mod : mods)
            {
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
            }
            registry.replace<common::components::attribute>(entity, attr.baseValue, value);
            registry.remove<common::components::recalculate>(entity);
        }
    }
}  // namespace common::systems
