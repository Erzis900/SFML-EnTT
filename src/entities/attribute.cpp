#include "attribute.hpp"

#include "components/attribute.hpp"
#include "components/health.hpp"
#include "components/maxHealth.hpp"
#include "components/recalculate.hpp"
#include "components/relationship.hpp"
#include "components/speed.hpp"

namespace common::entities
{
	entt::entity createAttribute(entt::registry &registry, entt::entity unit, common::entities::Stat stat, float initialValue)
	{
		auto entity = registry.create();
		auto &relationship = registry.emplace<common::components::relationship>(entity);
		registry.emplace<common::components::attribute>(entity, initialValue, initialValue);
		switch (stat)
		{
		case common::entities::Stat::Health:
			registry.emplace<common::components::health>(unit, initialValue);
			break;
		case common::entities::Stat::MaxHealth:
			registry.emplace<common::components::maxHealth>(unit, initialValue);
			break;
		case common::entities::Stat::Speed:
			registry.emplace<common::components::speed>(unit, initialValue);
			break;
		default:
			break;
		}
		return entity;
	}

	void initAttributes(entt::registry &registry, entt::entity entity)
	{
		registry.emplace<Attributes>(entity, Attributes{});

		auto &attributes = registry.get<Attributes>(entity).entities;
		attributes[Stat::Health] = createAttribute(registry, entity, Stat::Health, 50.f);
		attributes[Stat::MaxHealth] = createAttribute(registry, entity, Stat::MaxHealth, 50.f);
		attributes[Stat::Speed] = createAttribute(registry, entity, Stat::Speed, 180.f);
		attributes[Stat::Damage] = createAttribute(registry, entity, Stat::Damage, 10.f);
		attributes[Stat::MinDamage] = createAttribute(registry, entity, Stat::MinDamage, 0.f);
		attributes[Stat::MaxDamage] = createAttribute(registry, entity, Stat::MaxDamage, 5.f);
	}

	entt::entity createModifier(entt::registry &registry, entt::entity parent, common::entities::Scope scope, float value)
	{
		auto modifierEntity = registry.create();
		auto &relationship = registry.emplace<common::components::relationship>(modifierEntity);
		relationship.source = parent;
		registry.emplace<common::components::modifier>(modifierEntity, value, scope);

		return modifierEntity;
	}
	Stat getStat(std::string stat)
	{
		auto it = mapStat.find(stat);
		if (it != mapStat.end())
		{
			return it->second;
		}
		else
		{
			return Stat::NoneStat;
		}
	}
	Scope getScope(std::string scope)
	{
		auto it = mapScope.find(scope);
		if (it != mapScope.end())
		{
			return it->second;
		}
		else
		{
			return Scope::NoneScope;
		}
	}
}  // namespace common::entities
