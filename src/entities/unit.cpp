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

void createUnit(entt::registry &registry, entt::entity entity, sf::Vector2f &pos, float speed)
{
    registry.emplace<common::components::unit>(entity, true);
    registry.emplace<common::components::position>(entity, pos.x, pos.y);
    registry.emplace<common::components::direction>(entity, 0.f, 0.f);
    registry.emplace<common::components::speed>(entity, speed);
    auto &attributes = registry.emplace<common::components::children<common::entities::ATTRIBUTES_COUNT>>(entity, common::components::children<common::entities::ATTRIBUTES_COUNT>{}).entities;
    attributes[static_cast<std::size_t>(common::entities::Stat::Health)] = common::entities::createAttribute(registry, common::entities::Stat::Health, 100.f);
    attributes[static_cast<std::size_t>(common::entities::Stat::MaxHealth)] = common::entities::createAttribute(registry, common::entities::Stat::MaxHealth, 100.f);
    attributes[static_cast<std::size_t>(common::entities::Stat::Speed)] = common::entities::createAttribute(registry, common::entities::Stat::Speed, speed);
    auto modifier = common::entities::createModifier(registry, common::components::Scope::Flat, 100.f);
    registry.get<common::components::relationship>(attributes[static_cast<std::size_t>(common::entities::Stat::Speed)]).first_child = modifier;
    registry.emplace<common::components::recalculate>(attributes[static_cast<std::size_t>(common::entities::Stat::Speed)], true);
}