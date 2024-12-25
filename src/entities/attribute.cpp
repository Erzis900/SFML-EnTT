#include "attribute.hpp"

namespace common::entities
{
    entt::entity createAttribute(entt::registry &registry, common::entities::Stat stat, float initialValue)
    {
        auto entity = registry.create();
        auto &relationship = registry.emplace<common::components::relationship>(entity);
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
        registry.emplace<common::components::modifier>(modifierEntity, value, scope);

        return modifierEntity;
    }
    entt::entity addModifier(entt::registry &registry, entt::entity attributeEntity, common::components::Scope scope, float value)
    {
        auto modifierEntity = registry.create();
        registry.emplace<common::components::modifier>(modifierEntity, value, scope);

        auto &modificators = registry.get<common::components::relationship>(attributeEntity);
        auto modificator = modificators.first_child;

        while (modificator != entt::null)
        {
            if (registry.get<common::components::relationship>(modificator).next == entt::null)
            {
                registry.get<common::components::relationship>(modificator).next = modifierEntity;
                registry.get<common::components::relationship>(modifierEntity).prev = modificator;
                break;
            }
            modificator = registry.get<common::components::relationship>(modificator).next;
        }
        registry.emplace<common::components::recalculate>(attributeEntity, true);

        return attributeEntity;
    }
}
