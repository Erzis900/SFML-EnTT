#include <array>
#include "unit.hpp"
#include "components/position.hpp"
#include "components/speed.hpp"
#include "components/direction.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/relationship.hpp"
#include "components/children.hpp"
#include "components/unit.hpp"
#include "entities/attribute.hpp"

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f pos, sf::Vector2f dir, float speed, float health, float maxHealth)
{
    registry.emplace<common::components::unit>(entity, true);
    registry.emplace<common::components::position>(entity, pos.x, pos.y);
    registry.emplace<common::components::direction>(entity, dir.x, dir.y);
    registry.emplace<common::components::speed>(entity, speed);
    auto &attributes = registry.emplace<common::components::children<common::entities::ATTRIBUTES_COUNT>>(entity, common::components::children<common::entities::ATTRIBUTES_COUNT>{}).entities;
    attributes[static_cast<std::size_t>(common::entities::Stat::Health)] = common::entities::createAttribute(registry, common::entities::Stat::Health, health);
    attributes[static_cast<std::size_t>(common::entities::Stat::MaxHealth)] = common::entities::createAttribute(registry, common::entities::Stat::MaxHealth, maxHealth);
    attributes[static_cast<std::size_t>(common::entities::Stat::Speed)] = common::entities::createAttribute(registry, common::entities::Stat::Speed, speed);
    auto modifier1 = common::entities::createModifier(registry, common::components::Scope::Flat, 10.f);
    auto modifier2 = common::entities::addModifier(registry, modifier1, common::components::Scope::Flat, 10.f);
    auto modifier3 = common::entities::addModifier(registry, modifier2, common::components::Scope::Flat, 10.f);

    registry.get<common::components::relationship>(attributes[static_cast<std::size_t>(common::entities::Stat::Speed)]).first_child = modifier1;
    registry.emplace<common::components::recalculate>(attributes[static_cast<std::size_t>(common::entities::Stat::Speed)], true);
}