#include "attribute.hpp"

#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/speed.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/attribute.hpp"

namespace common::entities
{
    entt::entity createAttribute(entt::registry &registry, common::entities::Stat stat, float initialValue)
    {
        auto entity = registry.create();
        auto &relationship = registry.emplace<common::components::relationship>(entity);
        registry.emplace<common::components::attribute>(entity, initialValue, initialValue);
        switch (stat)
        {
        case common::entities::Stat::Health:
            registry.emplace<common::components::health>(entity, initialValue);
            break;
        case common::entities::Stat::MaxHealth:
            registry.emplace<common::components::maxHealth>(entity, initialValue);
            break;
        case common::entities::Stat::Speed:
            registry.emplace<common::components::speed>(entity, initialValue);
            break;
        default:
            break;
        }
        return entity;
    }
    entt::entity createModifier(entt::registry &registry, common::components::Scope scope, float value)
    {
        auto modifierEntity = registry.create();
        registry.emplace<common::components::relationship>(modifierEntity);
        registry.emplace<common::components::modifier>(modifierEntity, value, scope);

        return modifierEntity;
    }
    entt::entity addModifier(entt::registry &registry, entt::entity prevModifier, common::components::Scope scope, float value)
    {
        auto modifierEntity = registry.create();
        registry.emplace<common::components::relationship>(modifierEntity);
        registry.emplace<common::components::modifier>(modifierEntity, value, scope);
        registry.get<common::components::relationship>(modifierEntity).prev = prevModifier;
        registry.get<common::components::relationship>(prevModifier).next = modifierEntity;

        return modifierEntity;
    }
}
